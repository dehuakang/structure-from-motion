#ifndef DCMTKCOMMON
#define DCMTKCOMMON


#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmrt/drtplan.h>
#include <dcmtk/dcmrt/drmimage.h>
#include <dcmtk/dcmrt/drmdose.h>

#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>




// Load an RT Plan file and ge the iso vector.
void getRTPlanBeamISOCenter(double value[3],const char* fileName);

// Load an RT Dose file and access the scaled dose image.
void getRTDose(vtkSmartPointer<vtkImageData> imageData,const char* fileName);

#endif // DCMTKCOMMON

