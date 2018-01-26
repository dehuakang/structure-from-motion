#include "vtkcommon.h"


int main(int argc,char* argv[]){
    //
    if(argc<3){
        cout<<" Usage : "<<argv[0]<<" dir1  dir2"<<endl;
        return -1;
    }
    vtkSmartPointer<vtkPolyData> source;
    vtkSmartPointer<vtkPolyData> target;

    source=MakeMarchingCubeExractSurface(argv[1]);
    target=MakeMarchingCubeExractSurface(argv[2]);

    // Use vtkcleanpolydatafilter to delete 0 cell.
    vtkSmartPointer<vtkCleanPolyData> cleanFilter=vtkSmartPointer<vtkCleanPolyData>::New();
    cleanFilter->SetInputData(source);
    cleanFilter->Update();
    writePLYFileUsePolyData(cleanFilter->GetOutput(),"source.ply");
    cleanFilter->SetInputData(target);
    cleanFilter->Update();
    writePLYFileUsePolyData(cleanFilter->GetOutput(),"target.ply");

    // Output the polyDat by a ply file.
    writePLYFileUsePolyData(source,"source.ply");
    writePLYFileUsePolyData(target,"target.ply");

    //cout<<source->GetNumberOfPoints()<<","<<target->GetNumberOfPoints()<<endl;
    //cout<<source->GetNumberOfCells()<<","<<target->GetNumberOfCells()<<endl;
    vtkSmartPointer<vtkNamedColors> colors=vtkSmartPointer<vtkNamedColors>::New();
    vtkSmartPointer<vtkPolyDataMapper> sourceMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> targetMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    sourceMapper->SetInputData(source);
    targetMapper->SetInputData(target);
    sourceMapper->ScalarVisibilityOff();
    targetMapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> sourceActor=vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> targetActor=vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> origin=createOrigin();
    sourceActor->SetMapper(sourceMapper);
    sourceActor->GetProperty()->SetColor(colors->GetColor3d("tomato").GetData());
    targetActor->SetMapper(targetMapper);
    targetActor->GetProperty()->SetColor(colors->GetColor3d("banana").GetData());

    vtkSmartPointer<vtkRenderer> ren=vtkSmartPointer<vtkRenderer>::New();
    ren->AddActor(sourceActor);
    ren->AddActor(targetActor);
    ren->AddActor(origin);
    ren->SetBackground(0.1,0.2,0.3);

    vtkSmartPointer<vtkRenderWindow> renWin=vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren);
    renWin->SetSize(600,600);

    vtkSmartPointer<vtkRenderWindowInteractor> iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style=vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);
    iren->SetRenderWindow(renWin);
    //ren->Render();
    iren->Initialize();
    iren->Start();

    return 0;
}
