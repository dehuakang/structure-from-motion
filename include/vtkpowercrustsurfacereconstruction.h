#ifndef VTKPOWERCRUSTSURFACERECONSTRUCTION_H
#define VTKPOWERCRUSTSURFACERECONSTRUCTION_H
#pragma once
/*=========================================================================
 *
 * vtkPowerCrustSurfaceReconstruction algorithm reconstructs surfaces from
 * unorganized point data.
 * Copyright (C) 2014 Arash Akbarinia, Tim Hutton, Bruce Lamond
 *                    Dieter Pfeffer, Oliver Moss
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or any later
 * version.
 * Without any warranty.
 */
#include <vtkPolyData.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkSmartPointer.h>

class vtkPowerCrustSurfaceReconstruction:public vtkPolyDataAlgorithm{
public:
    static vtkPowerCrustSurfaceReconstruction* New();
    vtkTypeMacro(vtkPowerCrustSurfaceReconstruction,vtkPolyDataAlgorithm);
    void PrintSelf(ostream& os,vtkIndent indent);
    //This error function allows our ported code to report error messages neatly.
    //This is not for external use.
    void Error(const char* message);

    vtkSetMacro(EstimateR, double);
    vtkGetMacro(EstimateR, double);
    vtkGetMacro(Multlup,double);
    vtkGetMacro(MedialSurface,vtkPolyData*);

protected:
    vtkPowerCrustSurfaceReconstruction();
    ~vtkPowerCrustSurfaceReconstruction();

    //The main function that does the work
    virtual int RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector);
    virtual int FillInputPortInformation(int port, vtkInformation *info);

    void ComputeInputUpdateExtents(vtkDataObject* output);
    void ExecuteInfomation();

    vtkPolyData* MedialSurface;
    double EstimateR;
    double MultlUP;

private:
    vtkPowerCrustSurfaceReconstruction(const vtkPowerCrustSurfaceReconstruction&);
    void operator=(const vtkPowerCrustSurfaceReconstruction&);

};


#endif // VTKPOWERCRUSTSURFACERECONSTRUCTION

