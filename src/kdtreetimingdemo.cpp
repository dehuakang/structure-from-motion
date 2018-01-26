#include "vtkcommon.h"

static void RandomPointInBounds(vtkSmartPointer<vtkPolyData> polydata,double p[3]);
static double TimeKDTree(vtkSmartPointer<vtkPolyData> polydata,int maxPoints,int numberOfTrials);

int main(int,char* []){
    vtkSmartPointer<vtkPointSource> source=vtkSmartPointer<vtkPointSource>::New();
    source->SetNumberOfPoints(2000);
    source->SetRadius(100);
    source->SetCenter(vtkMath::Random(-10,10),
                      vtkMath::Random(-10,10),
                      vtkMath::Random(-10,10));
    source->SetDistributionToShell();
    source->Update();

    cout<<"Timing of kdtree..."<<endl;
    vector<pair<int,double>> results;
    int numberOfTrials=1000;
    for(int i=1;i<100;i++){
        double t=TimeKDTree(source->GetOutput(),i,numberOfTrials);
        pair<int,double> result(i,t);
        results.push_back(result);
    }

    // Create a table with some points in it.
    vtkSmartPointer<vtkTable> table=vtkSmartPointer<vtkTable>::New();
    vtkSmartPointer<vtkFloatArray> maxPointPerRegion=vtkSmartPointer<vtkFloatArray>::New();
    maxPointPerRegion->SetName("MaxPointsPerRegion");
    table->AddColumn(maxPointPerRegion);

    vtkSmartPointer<vtkFloatArray> runtime=vtkSmartPointer<vtkFloatArray>::New();
    runtime->SetName("Run time");
    table->AddColumn(runtime);

    // Fill in the table with some example values
    size_t numPoints=results.size();
    table->SetNumberOfRows(static_cast<vtkIdType>(numPoints));
    for(size_t i=0;i<numPoints;++i){
        table->SetValue(static_cast<vtkIdType>(i),0,results[i].first);
        table->SetValue(static_cast<vtkIdType>(i),1,results[i].second);
        //cout<<" Put "<<results[i].first<<","<<results[i].second<<" in the table"<<endl;
    }

    // Set up the view
    ViewChartXY(table,"Max Points Per Region","Run time");
    return 0;
}


void RandomPointInBounds(vtkSmartPointer<vtkPolyData> polydata, double p[3]){
    double bounds[6];
    polydata->GetBounds(bounds);

    double x=bounds[0]+(bounds[1]-bounds[0])*vtkMath::Random(0.0,1.0);
    double y=bounds[2]+(bounds[3]-bounds[2])*vtkMath::Random(0.0,1.0);
    double z=bounds[4]+(bounds[5]-bounds[4])*vtkMath::Random(0.0,1.0);

    p[0]=x;
    p[1]=y;
    p[2]=z;
}

double TimeKDTree(vtkSmartPointer<vtkPolyData> polydata, int maxPoints, int numberOfTrials){
    vtkSmartPointer<vtkTimerLog> timer=vtkSmartPointer<vtkTimerLog>::New();
    timer->StartTimer();

    vtkMath::RandomSeed(time(NULL));

    // Create kdtree
    vtkSmartPointer<vtkKdTreePointLocator> kdtree=vtkSmartPointer<vtkKdTreePointLocator>::New();
    kdtree->SetDataSet(polydata);
    kdtree->AutomaticOff();
    kdtree->SetMaxLevel(maxPoints);
    kdtree->BuildLocator();
    //cout<<"With maxLevel = "<<maxPoints<<" there are "<<kdtree->GetMaxLevel()<<" leaf nodes. "<<endl;

    for(int i=0;i<numberOfTrials;++i){
        double p[3];
        RandomPointInBounds(polydata,p);
        kdtree->FindClosestPoint(p);
    }


    timer->StopTimer();
    //cout<<" KDTree took "<<timer->GetElapsedTime()<<endl;
    return timer->GetElapsedTime();
}
