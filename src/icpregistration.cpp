#include "vtkcommon.h"

int main(int argc,char* argv[]){
    if(argc<3){
        cout<<" Usage : "<<argv[0]<<" source.ply target.ply"<<endl;
        return -1;
    }
    // Read ply file
    vtkSmartPointer<vtkPolyData> target=readPLYFile(argv[1]);
    vtkSmartPointer<vtkPolyData> source=readPLYFile(argv[2]);
    //cout<<source->GetNumberOfPoints()<<endl;
    // Set icp transform
    vtkSmartPointer<vtkIterativeClosestPointTransform> icp=vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
    icp->SetSource(source);
    icp->SetTarget(target);
    icp->GetLandmarkTransform()->SetModeToRigidBody();
    icp->SetMaximumNumberOfIterations(15);
    icp->Modified();
    icp->Update();

    // Get the result transform matrix
    vtkSmartPointer<vtkMatrix4x4> matrix=icp->GetMatrix();
    cout<<" The resulting matrix is : "<<*matrix<<endl;

    return 0;
}
