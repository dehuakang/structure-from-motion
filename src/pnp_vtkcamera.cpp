#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkRendererCollection.h>
#include <vtkWorldPointPicker.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCamera.h>
#include <vtkMatrix4x4.h>

using namespace std;

vector<cv::Point3f> objectPoints;
vector<cv::Point2f> imagePoints;

vtkSmartPointer<vtkRenderer> render=vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkRenderWindow> renderWindow=vtkSmartPointer<vtkRenderWindow>::New();
vtkSmartPointer<vtkMatrix4x4> projectorview=vtkSmartPointer<vtkMatrix4x4>::New();
vtkSmartPointer<vtkCamera> camera=vtkSmartPointer<vtkCamera>::New();

// Define interaction style
class MouseInteractorStyle:public vtkInteractorStyleTrackballCamera{
public:
    static MouseInteractorStyle* New();
    vtkTypeMacro(MouseInteractorStyle,vtkInteractorStyleTrackballCamera);

    virtual void OnLeftButtonDown() VTK_OVERRIDE{
        //cout<<" Picking pixel: "<<this->Interactor->GetEventPosition()[0]<<","
        //    <<this->Interactor->GetEventPosition()[1]<<endl;
        imagePoints.push_back(cv::Point2f(this->Interactor->GetEventPosition()[0],
                              this->Interactor->GetEventPosition()[1]));

        this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                this->Interactor->GetEventPosition()[1],
                0,
                this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
        double picked[3];
        this->Interactor->GetPicker()->GetPickPosition(picked);
        //cout<<" Picked Value: "<<picked[0]<<","<<picked[1]<<","<<picked[2]<<endl;
        objectPoints.push_back(cv::Point3f(picked[0],picked[1],picked[2]));
        int pointSize;
        pointSize=objectPoints.size();

        double cameraPos[3];
        cv::Mat cameraPosPnP(3,1,CV_64FC1);
        //camera->GetPosition(cameraPos);
        //cout<<"Camera Position is"<<cameraPos[0]<<","<<cameraPos[1]<<","<<cameraPos[2]<<endl;
        if(pointSize>=4){
            double cr[2];
            render->GetActiveCamera()->GetClippingRange(cr);
            int windowSize[2];
            renderWindow->GetInteractor()->GetSize(windowSize[0],windowSize[1]);
            projectorview=render->GetActiveCamera()->GetProjectionTransformMatrix(windowSize[0]/windowSize[1],cr[0],cr[1]);
            double Fy=projectorview->Element[1][1]*windowSize[1]/2.0;
            double uc=(double)windowSize[1]/2.0,vc=(double)windowSize[1]/2.0;
            double _k[9]={Fy,0,uc,0,Fy,vc,0,0,1};
            cv::Mat intrinsicMatrix(3,3,CV_64FC1,_k);
            double _d[4]={0,0,0,0};
            cv::Mat distCoeffs(1,4,CV_64F,_d);
            cv::Mat rvec(1,3,CV_64FC1);
            cv::Mat tvec(1,3,CV_64FC1);
            cv::solvePnP(objectPoints,imagePoints,intrinsicMatrix,distCoeffs,rvec,tvec,false,CV_EPNP);
            cv::Mat rot(3,3,CV_64FC1);
            cv::Rodrigues(rvec,rot);
            cv::Mat rotT(3,3,CV_64FC1);
            rotT=rot.t();
            render->SetActiveCamera(camera);
            cameraPosPnP=rotT*tvec;
            render->GetActiveCamera()->GetPosition(cameraPos);
            double focalP[3];
            camera->SetPosition(0,0,-10);
            camera->SetFocalPoint(0,0,0);
            render->GetActiveCamera()->GetFocalPoint(focalP);
            cout<<"*****************************************"<<endl;
            cout<<"Focla Point is "<<focalP[0]<<","<<focalP[1]<<","<<focalP[2]<<endl;
            cout<<"Camera Position is "<<cameraPos[0]<<","<<cameraPos[1]<<","<<cameraPos[2]<<endl;

            cout<<rot.at<double>(cv::Point(0,0))<<","<<rot.at<double>(cv::Point(0,1))<<","
               <<rot.at<double>(cv::Point(0,2))<<endl;
            cout<<rot.ptr<double>(0)[0]<<","<<rot.ptr<double>(1)[0]<<","<<rot.ptr<double>(2)[0]<<endl;
            vtkInteractorStyleTrackballCamera::OnLeftButtonDown();

        }
    }
    // Forwad events

};

vtkStandardNewMacro(MouseInteractorStyle);

int main(int argc,char* argv[]){
    //
    vtkSmartPointer<vtkSphereSource> sphere=vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetRadius(2);
    sphere->Update();

    vtkSmartPointer<vtkWorldPointPicker> worldPointPicker=vtkSmartPointer<vtkWorldPointPicker>::New();
    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphere->GetOutputPort());
    vtkSmartPointer<vtkActor> actor=vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    //Create a renderer,render window,and interacor
    render->SetActiveCamera(camera);
    camera->SetPosition(0,0,-10);
    camera->SetFocalPoint(0,0,0);
    renderWindow->AddRenderer(render);

    vtkSmartPointer<vtkRenderWindowInteractor> iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetPicker(worldPointPicker);
    iren->SetRenderWindow(renderWindow);
    vtkSmartPointer<MouseInteractorStyle> style=vtkSmartPointer<MouseInteractorStyle>::New();
    iren->SetInteractorStyle(style);

    render->AddActor(actor);
    render->SetBackground(1,1,1);

    iren->Initialize();
    iren->Start();

    return 0;
}
