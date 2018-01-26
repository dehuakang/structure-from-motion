#include "vtkcommon.h"


int main(int,char*[]){
    vtkSmartPointer<vtkSphereSource> sphere=vtkSmartPointer<vtkSphereSource>::New();
    //sphere->SetThetaResolution(50);
    //sphere->SetPhiResolution(50);
    vtkSmartPointer<vtkConeSource> cone=vtkSmartPointer<vtkConeSource>::New();
    //fileter
    vtkSmartPointer<vtkGlyph3D> glyph=vtkSmartPointer<vtkGlyph3D>::New();
    glyph->SetInputConnection(sphere->GetOutputPort());
    glyph->SetSourceConnection(cone->GetOutputPort());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.2);

    // composite new polygon
    vtkSmartPointer<vtkAppendPolyData> apd=vtkSmartPointer<vtkAppendPolyData>::New();
    apd->AddInputConnection(glyph->GetOutputPort());
    apd->AddInputConnection(sphere->GetOutputPort());

    // Mapper
    vtkSmartPointer<vtkPolyDataMapper> maceMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    maceMapper->SetInputConnection(apd->GetOutputPort());
    // Actor
    vtkSmartPointer<vtkLODActor> maceActor=vtkSmartPointer<vtkLODActor>::New();
    maceActor->SetMapper(maceMapper);
    maceActor->VisibilityOn();

    // Define a plane function
    vtkSmartPointer<vtkPlane> plane=vtkSmartPointer<vtkPlane>::New();
    vtkSmartPointer<vtkClipPolyData> clipper=vtkSmartPointer<vtkClipPolyData>::New();
    clipper->SetInputConnection(apd->GetOutputPort());
    clipper->SetClipFunction(plane);
    clipper->SetValue(0.3);
    clipper->InsideOutOn();

    vtkSmartPointer<vtkPolyDataMapper> selectMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    selectMapper->SetInputConnection(clipper->GetOutputPort());

    vtkSmartPointer<vtkLODActor> selectActor=vtkSmartPointer<vtkLODActor>::New();
    selectActor->SetMapper(selectMapper);
    selectActor->GetProperty()->SetColor(0,1,0);
    selectActor->VisibilityOff();
    selectActor->SetScale(1.01,1.01,1.01);

    // Create the RenderWindow ,renderer and both Actors
    vtkSmartPointer<vtkRenderer> ren=vtkSmartPointer<vtkRenderer>::New();
    ren->SetBackground(0.1,0.2,0.4);
    ren->AddActor(maceActor);
    ren->AddActor(selectActor);
    ren->AddActor(createOrigin());

    vtkSmartPointer<vtkRenderWindow> renWin=vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren);
    renWin->SetSize(600,600);
    vtkSmartPointer<vtkRenderWindowInteractor> iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style=vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);
    iren->SetRenderWindow(renWin);
    vtkSmartPointer<vtkTIPWCallback> myCallback=vtkSmartPointer<vtkTIPWCallback>::New();
    myCallback->plane=plane;
    myCallback->actor=selectActor;

    vtkSmartPointer<vtkImplicitPlaneWidget> planeWidget=vtkSmartPointer<vtkImplicitPlaneWidget>::New();
    planeWidget->SetInteractor(iren);
    planeWidget->SetPlaceFactor(1.25);
    planeWidget->SetInputConnection(glyph->GetOutputPort());
    planeWidget->PlaceWidget();
    planeWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);
    planeWidget->On();

    iren->Initialize();
    iren->Start();
    return 0;

}
