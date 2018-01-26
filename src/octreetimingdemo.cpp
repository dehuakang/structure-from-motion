#include "vtkcommon.h"

static void RandomPointInBounds(vtkPolyData* polydata,double p[3]);
static double TimeOctree(vtkPolyData* polydata,int maxPoints,int numberOfTrials);

int main(int,char* []){
    vtkSmartPointer<vtkSphereSource> source=vtkSmartPointer<vtkSphereSource>::New();
    source->SetThetaResolution(30);
    source->SetPhiResolution(30);
    source->Update();
    cout<<" Timing octree... "<<endl;
    vector<pair<int,double>> results;
    int numberOfTrials=1000;
    for(int i=1;i<100;i++){
        double t=TimeOctree(source->GetOutput(),i,numberOfTrials);
        pair<int,double> result(i,t);
        results.push_back(result);
    }
    // Create a table with some points in it.
    vtkSmartPointer<vtkTable> table=vtkSmartPointer<vtkTable>::New();
    vtkSmartPointer<vtkFloatArray> maxPointsPerRegion=vtkSmartPointer<vtkFloatArray>::New();
    maxPointsPerRegion->SetName("MaxPointPerRegion");
    table->AddColumn(maxPointsPerRegion);

    vtkSmartPointer<vtkFloatArray> runtime=vtkSmartPointer<vtkFloatArray>::New();
    runtime->SetName("Run time");
    table->AddColumn(runtime);
    // Fill in the table with some example values
    size_t numPoints=results.size();
    table->SetNumberOfRows(static_cast<vtkIdType>(numPoints));
    for(size_t i=0;i<numPoints;i++){
        table->SetValue(static_cast<vtkIdType>(i),0,results[i].first);
        table->SetValue(static_cast<vtkIdType>(i),1,results[i].second);
    }
    ViewChartXY(table,"Max Point Per Region","Run Time");
    return 0;
}

void RandomPointInBounds(vtkPolyData *polydata, double p[]){
    double bounds[6];
    polydata->GetBounds(bounds);

    double x=bounds[0]+(bounds[1]-bounds[0])*vtkMath::Random(0.0,1.0);
    double y=bounds[2]+(bounds[3]-bounds[2])*vtkMath::Random(0.0,1.0);
    double z=bounds[4]+(bounds[5]-bounds[4])*vtkMath::Random(0.0,1.0);
    p[0]=x;p[1]=y;p[2]=z;
}
double TimeOctree(vtkPolyData *polydata, int maxPoints, int numberOfTrials){
    vtkSmartPointer<vtkTimerLog> timer=vtkSmartPointer<vtkTimerLog>::New();
    timer->StartTimer();

    vtkMath::RandomSeed(0);
    // Create the tree.
    vtkSmartPointer<vtkOctreePointLocator> octree=vtkSmartPointer<vtkOctreePointLocator>::New();
    octree->SetDataSet(polydata);
    octree->SetMaximumPointsPerRegion(maxPoints);
    octree->BuildLocator();

    cout<<" With maxPoints = "<<maxPoints<<" there are "<<octree->GetNumberOfLeafNodes()<<" leaf nodes."<<endl;

    for(int i=0;i<numberOfTrials;++i){
        double p[3];
        RandomPointInBounds(polydata,p);
        octree->FindClosestPoint(p);
    }
    timer->StopTimer();
    cout<<" Octree took "<<timer->GetElapsedTime()<<endl;
    return timer->GetElapsedTime();
}
