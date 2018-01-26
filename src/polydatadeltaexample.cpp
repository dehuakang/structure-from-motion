#include "vtkpolydatadelta.h"
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkDataArray.h>
#include <vtkDoubleArray.h>
#include <vtkGlyph3D.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLookupTable.h>
#include <vtkMath.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkScalarBarActor.h>
#include <vtkSphereSource.h>
#include <vtkPLYReader.h>
#include <iostream>
#include <string>

using namespace  std;

int main(int argc,char* argv[]){
    if(argc<3){
        cout<<" Usage: "<<argv[0]<<" filename.ply filename.ply"<<endl;
        return -1;
    }
    string mesh1Name=argv[1];
    string mesh2Name=argv[2];

    vtkSmartPointer<vtkPLYReader> reader1=vtkSmartPointer<vtkPLYReader>::New();
    reader1->SetFileName(mesh1Name.c_str());
    reader1->Update();

    vtkSmartPointer<vtkPLYReader> reader2=vtkSmartPointer<vtkPLYReader>::New();
    reader2->SetFileName(mesh2Name.c_str());
    reader2->Update();

    // Compare the meshes
    vtkSmartPointer<vtkPolyDataDelta> polyDataDelta=vtkSmartPointer<vtkPolyDataDelta>::New();
    polyDataDelta->SetInputConnection(0,reader1->GetOutputPort());
    polyDataDelta->SetInputConnection(1,reader2->GetOutputPort());
    polyDataDelta->Update();

    // Create lookup table
    vtkSmartPointer<vtkLookupTable> lookupTable=vtkSmartPointer<vtkLookupTable>::New();
    double range[2];
    vtkDoubleArray::SafeDownCast(polyDataDelta->GetOutput()->GetPointData()->GetArray("Distances"))->GetRange(range);
    cout<<"Range: "<<range[0]<<"  "<<range[1]<<endl;
    lookupTable->SetRange(range);
    lookupTable->Build();

    // Create scalarbar
    vtkSmartPointer<vtkScalarBarActor> scalarBar=vtkSmartPointer<vtkScalarBarActor>::New();
    scalarBar->SetLookupTable(lookupTable);
    scalarBar->SetTitle("Mesh Distance");

    // Create normal glyph
    vtkSmartPointer<vtkGlyph3D> glyph=vtkSmartPointer<vtkGlyph3D>::New();
    glyph->SetInputData(polyDataDelta->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->OrientOn();

    // Set to mappers
    vtkSmartPointer<vtkPolyDataMapper> mapperA=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapperA->SetInputData(polyDataDelta->GetOutput());
    mapperA->SetScalarRange(range);
    mapperA->SetLookupTable(lookupTable);

    vtkSmartPointer<vtkPolyDataMapper> mapperB=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapperB->SetInputConnection(reader2->GetOutputPort());

    vtkSmartPointer<vtkPolyDataMapper> normalMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    normalMapper->SetInputConnection(glyph->GetOutputPort());

    //Set to actors
    vtkSmartPointer<vtkActor> actorA=vtkSmartPointer<vtkActor>::New();
    actorA->SetMapper(mapperA);
    vtkSmartPointer<vtkActor> actorB=vtkSmartPointer<vtkActor>::New();
    actorB->SetMapper(mapperB);
    actorB->GetProperty()->SetOpacity(0.3);

    vtkSmartPointer<vtkActor> normalActor=vtkSmartPointer<vtkActor>::New();
    normalActor->SetMapper(normalMapper);
    normalActor->GetProperty()->SetOpacity(0.8);
    normalActor->GetProperty()->SetColor(0.,.2,0.);

    // Visualize
    vtkSmartPointer<vtkRenderer> ren=vtkSmartPointer<vtkRenderer>::New();
    ren->AddActor(actorA);

    bool displayNormal=0;
    if(displayNormal){
        ren->AddActor(normalActor);
    }
    ren->AddActor(actorB);
    ren->AddActor2D(scalarBar);

    vtkSmartPointer<vtkRenderWindow> renWin=vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren);
    renWin->SetSize(800,800);

    vtkSmartPointer<vtkRenderWindowInteractor> iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style=vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);
    iren->SetRenderWindow(renWin);

    iren->Initialize();
    iren->Start();

    return 0;
}
