#ifndef VTKPOLYDATADELTA_H
#define VTKPOLYDATADELTA_H

#include <vtkDoubleArray.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkModifiedBSPTree.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkSmartPointer.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkPolyDataAlgorithm.h>

class vtkPolyDataDelta:public vtkPolyDataAlgorithm{
public:
    vtkTypeMacro(vtkPolyDataDelta,vtkPolyDataAlgorithm);
    static vtkPolyDataDelta *New();
protected:
    vtkPolyDataDelta();
    ~vtkPolyDataDelta(){}

    int FillInputPortInformation(int port, vtkInformation *info) VTK_OVERRIDE;
    int RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector) VTK_OVERRIDE;

private:
    vtkPolyDataDelta(const vtkPolyDataDelta&);
    void operator =(const vtkPolyDataDelta&);





};

#endif // VTKPOLYDATADELTA

