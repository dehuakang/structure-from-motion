#ifndef VTKCOMMON_H
#define VTKCOMMON_H
#pragma once

// VTK include
#include <vtkVersion.h>
#include <vtkCommand.h>
#include <vtkImplicitPlaneWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkGlyph3D.h>
#include <vtkPolyDataMapper.h>
#include <vtkLODActor.h>
#include <vtkPlane.h>
#include <vtkClipPolyData.h>
#include <vtkAppendPolyData.h>
#include <vtkPLYReader.h>
#include <vtkPLYWriter.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointSource.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkAxis.h>
#include <vtkTimerLog.h>
#include <vtkMath.h>
#include <vtkIdList.h>
#include <vtkKdTreePointLocator.h>
#include <vtkOctreePointLocator.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkTable.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkMarchingCubes.h>
#include <vtkDICOMImageReader.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkCleanPolyData.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkIterativeClosestPointTransform.h>
#include <vtkMatrix4x4.h>
#include <vtkLandmarkTransform.h>
#include <vtkCurvatures.h>
#include <vtkLookupTable.h>
#include <vtkColorTransferFunction.h>
#include <vtkColorSeries.h>
#include <vtkVolume.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkOBJReader.h>
#include <vtkSTLReader.h>
#include <vtksys/SystemTools.hxx>

// C++ include
#include <time.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

class vtkTIPWCallback:public vtkCommand{
public:
    static vtkTIPWCallback *New(){
        return new vtkTIPWCallback;
    }
    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData){
        vtkImplicitPlaneWidget *planeWidget=reinterpret_cast<vtkImplicitPlaneWidget*>(caller);
        planeWidget->GetPlane(this->plane);
        this->actor->VisibilityOn();
    }
    vtkTIPWCallback():plane(0),actor(0){}
    vtkPlane *plane;
    vtkActor *actor;
};

// Read and Write an PLY format file of vtkPolyData data type.
void writePLYFileUsePolyData(vtkSmartPointer<vtkPolyData> polyData,const char* fileName);
vtkSmartPointer<vtkPolyData> readPLYFile(const char* fileName);

// Display a Actor in a renderer Window
void showRenderWindowWithActor(vtkSmartPointer<vtkActor> actor);

// Create an original point in a scene
vtkSmartPointer<vtkActor> createOrigin();

// Study of scalars tow functions to be used here
void TypeSpecific();
void NonTypeSpecific();

// Chart graph
void ViewChartXY(vtkSmartPointer<vtkTable> table,string xTitle,string yTitle);
// End of two function

vtkSmartPointer<vtkPolyData> MakeMarchingCubeExractSurface(const char *folderName);
vtkSmartPointer<vtkVolume> ReadDICOMreturnVolume(const char *folderName);
vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName);

#endif // VTKCOMMON

