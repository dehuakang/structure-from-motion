#include "vtkpowercrustsurfacereconstruction.h"
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkInformation.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>

#include <assert.h>
#include <float.h>

//
class vtkPowerCrustSurfaceReconstruction:public std::exception{
public:
    vtkPowerCrustSurfaceReconstruction(const char* m="vtkPowerCrustSurfaceReconstructionException!"):msg(m){}
    ~vtkPowerCrustSurfaceReconstruction() throw(){}
    virtual const char* what() const throw(){
        return msg;
    }

private:
    const char* msg;
};

typedef double Coord;
typedef Coord* point;
typedef point site;

#define MAXBLOCKS 10000
#define Nobj 10000

#define STORAGE_GLOBALS(X)
extern size_t X##_size;
extern X *X##_list;

