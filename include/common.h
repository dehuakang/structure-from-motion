#ifndef COMMON_H
#define COMMON_H

#pragma once

// C++ std
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;
// VTK include files
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>
#include <vtkPLYReader.h>
#include <vtkPLYWriter.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtksys/SystemTools.hxx>
#include <vtkXMLPolyDataReader.h>
#include <vtkOBJReader.h>
#include <vtkSTLReader.h>
#include <vtkPointSource.h>
#include <vtkMath.h>
#include <vtkMatrix4x4.h>
#include <vtkExtractSurface.h>
#include <vtkSignedDistance.h>
#include <vtkPCANormalEstimation.h>
#include <vtkPointData.h>
#include <vtkDICOMImageReader.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkVolume.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkCamera.h>
#include <vtkLandmarkTransform.h>
#include <vtkIterativeClosestPointTransform.h>
#include <vtkCleanPolyData.h>
#include <vtkCurvatures.h>
#include <vtkLookupTable.h>
#include <vtkColorSeries.h>
#include <vtkScalarBarActor.h>
#include <vtkGlyph3D.h>
#include <vtkArrowSource.h>


// PCL include files



// OpenCV include files



// DCMTK include files


// Define function heads

vtkSmartPointer<vtkActor> createOrigin();
vtkSmartPointer<vtkActor> createPoint();
void showRenderWindowWithActor(vtkSmartPointer<vtkActor> actor);

vtkSmartPointer<vtkPolyData> readPLYFile(const char* fileName);
void writePLYFileUsePolyData(vtkSmartPointer<vtkPolyData> polyData,const char* fileName);

void DisplayNamedColorNames(vtkSmartPointer<vtkNamedColors> colors);
vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName);
vtkSmartPointer<vtkPolyDataAlgorithm> MakeExtractSurface(vtkPolyData *);
vtkSmartPointer<vtkPolyData> MakeMarchingCubeExractSurface(const char* folderName);
vtkSmartPointer<vtkVolume> readDICOMreturnVolume(const char* folderName);

bool GetPointNormals(vtkSmartPointer<vtkPolyData> polydata);
bool GetCellNormals(vtkSmartPointer<vtkPolyData> polydata);
void TestPointNormals(vtkSmartPointer<vtkPolyData> polydata);
void TestCellNormals(vtkSmartPointer<vtkPolyData> polydata);
#endif // COMMON

