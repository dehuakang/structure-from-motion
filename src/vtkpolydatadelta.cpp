#include "vtkpolydatadelta.h"

vtkStandardNewMacro(vtkPolyDataDelta);
vtkPolyDataDelta::vtkPolyDataDelta(){
    this->SetNumberOfInputPorts(2);
}

int vtkPolyDataDelta::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector){
    // Get the 2 input meshes
    vtkInformation *inInfo0=inputVector[0]->GetInformationObject(0);
    vtkPolyData *meshA=vtkPolyData::SafeDownCast(inInfo0->Get(vtkDataObject::DATA_OBJECT()));

    vtkInformation *inInfo1=inputVector[1]->GetInformationObject(0);
    vtkPolyData *meshB=vtkPolyData::SafeDownCast(inInfo1->Get(vtkDataObject::DATA_OBJECT()));

    // Get the output
    vtkInformation *outInfo=outputVector->GetInformationObject(0);
    vtkPolyData *outputMesh=vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));
    outputMesh->ShallowCopy(meshA);

    // Calculate BSP tree
    vtkSmartPointer<vtkModifiedBSPTree> bspTree=vtkSmartPointer<vtkModifiedBSPTree>::New();
    bspTree->SetDataSet(meshB);
    bspTree->BuildLocator();

    // Calculate meshA normals
    vtkSmartPointer<vtkPolyDataNormals> normals=vtkSmartPointer<vtkPolyDataNormals>::New();
    normals->SetInputData(meshA);
    normals->ComputeCellNormalsOff();
    normals->ComputeCellNormalsOn();
    normals->SplittingOff();
    normals->Update();
    vtkSmartPointer<vtkDataArray> normalData=normals->GetOutput()->GetPointData()->GetNormals();

    // Diff Calculation
    double normal[3];     // stores normal extracted for a single point
    double refPt[3];      // stores the current point in meshA
    double vectPtN[3];    // end point of search line in -'ve normal direction
    double vectPtP[3];    // end point of search line in +'ve normal direction
    double x[3];          // intersection point on cell
    double tP;            // length along +'ve search line
    double tN;            // length along -'ve search line
    double pcoords[3];
    int subId;
    int intersectP;
    int intersectN;
    double dist;
    double max=-1.e22;
    double min=1.e22;
    double SEARCHLENGTH=100.;
    double TOL=0.001;     // bspTree tolerance

    // Create array to store distance
    vtkSmartPointer<vtkDoubleArray> distArray=vtkSmartPointer<vtkDoubleArray>::New();
    distArray->SetNumberOfComponents(1);
    distArray->SetName("Distances");
    distArray->SetNumberOfValues(meshA->GetNumberOfPoints());

    // Loop through each point in meshA
    for(int i=0;i<meshA->GetNumberOfPoints();++i){
        normalData->GetTuple(i,normal);        // get normal at point
        meshA->GetPoint(i,refPt);              // get point location

        // Create end points for lines about the +'ve and -'ve direction of the point normal
        vectPtN[0]=refPt[0]-SEARCHLENGTH*normal[0];
        vectPtN[1]=refPt[1]-SEARCHLENGTH*normal[1];
        vectPtN[2]=refPt[2]-SEARCHLENGTH*normal[2];

        vectPtP[0]=refPt[0]+SEARCHLENGTH*normal[0];
        vectPtP[1]=refPt[1]+SEARCHLENGTH*normal[1];
        vectPtP[2]=refPt[2]+SEARCHLENGTH*normal[2];

        // Check the intersection in the +'ve and -'ve direction: these must be separated since bspTree
        // returns the first intersection when traversing the line segment, which may not be the closest cell.
        // This use to line segments, both traversed from the point of interest. This then results in the
        // closest intersection in both the +'ve and -'ve direction.
        intersectN=bspTree->IntersectWithLine(refPt,vectPtN,TOL,tN,x,pcoords,subId);
        intersectP=bspTree->IntersectWithLine(refPt,vectPtP,TOL,tP,x,pcoords,subId);

        // Logic to chech for the closet intersection
        if(intersectN==0 && intersectP==0){
            dist=0;
        }
        else if(intersectN==0 && intersectP!=0){
            dist=tP*SEARCHLENGTH;
        }
        else if(intersectP==0 && intersectN!=0){
            dist=-tN*SEARCHLENGTH;
        }
        else{
            if(tN<tP){
                dist=-tN*SEARCHLENGTH;
            }
            else{
                dist=tP*SEARCHLENGTH;
            }
        }
        // Store the min and max values
        if(dist>max){
            max=dist;
        }
        else if(dist<min){
            min=dist;
        }
        distArray->SetValue(i,dist);
    }

    outputMesh->GetPointData()->SetScalars(distArray);
    return 1;
}

int vtkPolyDataDelta::FillInputPortInformation(int port, vtkInformation *info){
    // this filter has two input ports
    if(port==0){
        info->Set(vtkDataObject::DATA_TYPE_NAME(),"vtkPolyData");
        return 1;
    }
    else if(port==1){
        info->Set(vtkDataObject::DATA_TYPE_NAME(),"vtkPolyData");
        return 1;
    }
    return 0;
}
