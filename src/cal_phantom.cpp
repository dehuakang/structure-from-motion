#include "common.h"
#include <vtkWorldPointPicker.h>
#include <vtkRendererCollection.h>
vtkSmartPointer<vtkRenderer> render=vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkRenderWindow> renderWindow=vtkSmartPointer<vtkRenderWindow>::New();
vtkSmartPointer<vtkCamera> camera=vtkSmartPointer<vtkCamera>::New();

class MouseInteractorStyle:public vtkInteractorStyleTrackballCamera{
public:
    static MouseInteractorStyle* New();
    vtkTypeMacro(MouseInteractorStyle,vtkInteractorStyleTrackballCamera);

    virtual void OnLeftButtonDown() VTK_OVERRIDE{
        this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                this->Interactor->GetEventPosition()[1],
                0,
                this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
        double picked[3];
        this->Interactor->GetPicker()->GetPickPosition(picked);
        cout<<" Picked value: "<<picked[0]<<","<<picked[1]<<","<<picked[2]<<endl;
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }
};

vtkStandardNewMacro(MouseInteractorStyle);

int main(int argc,char* argv[]){
    if(argc<2){
        cout<<" Usage: "<<argv[0]<<"dicomDir"<<endl;
        return -1;
    }
    vtkSmartPointer<vtkPolyData> data=MakeMarchingCubeExractSurface(argv[1]);
    //writePLYFileUsePolyData(data,"cali_phantom.ply");
    //vtkSmartPointer<vtkPolyData> data=readPLYFile("cali_phantom_.ply");
    vtkSmartPointer<vtkActor> originalActor=createOrigin();
    vtkSmartPointer<vtkWorldPointPicker> worldPicker=vtkSmartPointer<vtkWorldPointPicker>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(data);
    mapper->ScalarVisibilityOff();
    vtkSmartPointer<vtkNamedColors> colors=vtkSmartPointer<vtkNamedColors>::New();
    vtkSmartPointer<vtkActor> actor=vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("flesh").GetData());
    vtkSmartPointer<vtkRenderWindowInteractor> iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindow->AddRenderer(render);
    renderWindow->SetSize(600,600);
    render->AddActor(actor);
    render->AddActor(originalActor);
    render->SetBackground(0.1,0.2,0.4);
    iren->SetPicker(worldPicker);
    iren->SetRenderWindow(renderWindow);
    vtkSmartPointer<MouseInteractorStyle> style=vtkSmartPointer<MouseInteractorStyle>::New();
    iren->SetInteractorStyle(style);
    iren->Initialize();

    iren->Start();
    return 0;
}
