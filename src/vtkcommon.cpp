#include "vtkcommon.h"

//

void writePLYFileUsePolyData(vtkSmartPointer<vtkPolyData> polyData,const char* fileName){
    // Write PLY file use polyData.
    vtkSmartPointer<vtkPLYWriter> plyWriter=vtkSmartPointer<vtkPLYWriter>::New();
    plyWriter->SetFileName(fileName);
    plyWriter->SetInputData(polyData);
    plyWriter->Write();
}

vtkSmartPointer<vtkPolyData> readPLYFile(const char* fileName){
    // Read PLY file.
    vtkSmartPointer<vtkPLYReader> plyReader=vtkSmartPointer<vtkPLYReader>::New();
    plyReader->SetFileName(fileName);
    plyReader->Update();
    //vtkSmartPointer<vtkPolyData> polyData=plyReader->GetOutput();
    vtkSmartPointer<vtkPolyData> polyData=vtkSmartPointer<vtkPolyData>::New();
    polyData->ShallowCopy(plyReader->GetOutput());
    return polyData;
}

void showRenderWindowWithActor(vtkSmartPointer<vtkActor> actor){
    // Pass an actor to show it in a renderwindow
    vtkSmartPointer<vtkNamedColors> colors=vtkSmartPointer<vtkNamedColors>::New();
    vtkSmartPointer<vtkRenderer> renderer=vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.1,0.2,0.3);
    vtkSmartPointer<vtkRenderWindow> renderWindow=vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(400,400);
    vtkSmartPointer<vtkRenderWindowInteractor> iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style=vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);
    iren->SetRenderWindow(renderWindow);
    iren->Start();
}


vtkSmartPointer<vtkActor> createOrigin(){
    // Use point, vertex to create a point and the set the point position.
    vtkSmartPointer<vtkActor> actor=vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPoints> ps=vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> vert=vtkSmartPointer<vtkCellArray>::New();
    vtkIdType pid[1];
    pid[0]=ps->InsertNextPoint(0,0,0);
    vert->InsertNextCell(1,pid);
    vtkSmartPointer<vtkPolyData> polyData=vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(ps);
    polyData->SetVerts(vert);

    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1,0,0);
    actor->GetProperty()->SetPointSize(8);
    return actor;
}

// Use in scalars study.
void TypeSpecific(){
    // Create a point set
    vtkSmartPointer<vtkPoints> points=vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0,0,0);
    points->InsertNextPoint(1,0,0);

    vtkSmartPointer<vtkPolyData> polydata=vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);

    vtkSmartPointer<vtkDoubleArray> weights=vtkSmartPointer<vtkDoubleArray>::New();
    weights->SetNumberOfValues(2);
    weights->SetValue(0,1);
    weights->SetValue(1,2);

    polydata->GetPointData()->SetScalars(weights);

    double weight=vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetScalars())->GetValue(0);
    cout<<" double weight: "<<weight<<endl;
}

void NonTypeSpecific(){
    vtkSmartPointer<vtkPoints> points=vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0,0,0);
    points->InsertNextPoint(1,0,0);

    vtkSmartPointer<vtkPolyData> polydata=vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);

    vtkSmartPointer<vtkDoubleArray> weights=vtkSmartPointer<vtkDoubleArray>::New();
    weights->SetNumberOfValues(2);
    weights->SetValue(0,1);
    weights->SetValue(1,2);

    polydata->GetPointData()->SetScalars(weights);

    double weight=polydata->GetPointData()->GetScalars()->GetComponent(0,0);
    cout<<" double weitht: "<<weight<<endl;

    double weightf=polydata->GetPointData()->GetScalars()->GetComponent(0,0);
    cout<< "float weight: "<<weightf<<endl;
}

// chart
void ViewChartXY(vtkSmartPointer<vtkTable> table, string xTitle, string yTitle){
    // Set up the view
    vtkSmartPointer<vtkContextView> view=vtkSmartPointer<vtkContextView>::New();
    view->GetRenderer()->SetBackground(1.0,1.0,1.0);

    // Add multiple line plots, setting the colors etc
    vtkSmartPointer<vtkChartXY> chart=vtkSmartPointer<vtkChartXY>::New();
    view->GetScene()->AddItem(chart);
    vtkPlot *line=chart->AddPlot(vtkChart::LINE);
    line->SetInputData(table,0,1);
    line->SetColor(0,255,0,255);
    line->SetWidth(3.0);
    line->GetXAxis()->SetTitle(xTitle);
    line->GetYAxis()->SetTitle(yTitle);

    view->GetRenderWindow()->SetMultiSamples(0);
    view->GetRenderWindow()->SetSize(600,300);

    // Start interactor
    view->GetInteractor()->Initialize();
    view->GetInteractor()->Start();
}
vtkSmartPointer<vtkPolyData> MakeMarchingCubeExractSurface(const char *folderName){
    // Reade a series dicom files in a folder
    vtkSmartPointer<vtkDICOMImageReader> dicomReader=vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomReader->SetDirectoryName(folderName);
    dicomReader->Update();
    // cos(xx')=1 cos(yy')=-1  cos(zz')=-1
    double ImagePositionPatient[3];
    ImagePositionPatient[0]=dicomReader->GetImagePositionPatient()[0];
    ImagePositionPatient[1]=-dicomReader->GetImagePositionPatient()[1];
    ImagePositionPatient[2]=-dicomReader->GetImagePositionPatient()[2];
    ImagePositionPatient[1]-=dicomReader->GetDataExtent()[3]*dicomReader->GetPixelSpacing()[1];
    ImagePositionPatient[2]-=dicomReader->GetDataExtent()[5]*dicomReader->GetPixelSpacing()[2];

    // Create a 3D model using marching cubes
    vtkSmartPointer<vtkMarchingCubes> mc=vtkSmartPointer<vtkMarchingCubes>::New();
    mc->SetInputConnection(dicomReader->GetOutputPort());
    mc->ComputeNormalsOn();
    mc->ComputeGradientsOn();
    mc->SetValue(0,-150);   //second value acts as threshold.

    // To remain largest region
    vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter=vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
    confilter->SetInputConnection(mc->GetOutputPort());
    confilter->SetExtractionModeToLargestRegion();
    //confilter->SetExtractionModeToAllRegions();
    confilter->Update();

    vtkSmartPointer<vtkCleanPolyData> cleanFilter=vtkSmartPointer<vtkCleanPolyData>::New();
    cleanFilter->SetInputConnection(confilter->GetOutputPort());
    cleanFilter->Update();

    vtkSmartPointer<vtkTransform> originalTransform=vtkSmartPointer<vtkTransform>::New();
    originalTransform->Translate(ImagePositionPatient);
    vtkSmartPointer<vtkTransformFilter> filter=vtkSmartPointer<vtkTransformFilter>::New();
    filter->SetTransform(originalTransform);
    filter->SetInputConnection(cleanFilter->GetOutputPort());
    filter->Update();
    vtkSmartPointer<vtkPolyData> polyData=vtkSmartPointer<vtkPolyData>::New();
    polyData->ShallowCopy(filter->GetOutput());
    return polyData;
}

//
vtkSmartPointer<vtkVolume> ReadDICOMreturnVolume(const char *folderName){
    //
    vtkSmartPointer<vtkDICOMImageReader> reader=vtkSmartPointer<vtkDICOMImageReader>::New();
    reader->SetDirectoryName(folderName);
    reader->Update();

    // A ray-cast mapper is needed to do the ray-casting.
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper=vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
    volumeMapper->SetInputConnection(reader->GetOutputPort());

    // Color transfer function. color for flesh(500-1000), color for bone (1000 and above).
    vtkSmartPointer<vtkColorTransferFunction> volumeColor=vtkSmartPointer<vtkColorTransferFunction>::New();
    volumeColor->AddRGBPoint(0,0.0,0.0,0.0);
    volumeColor->AddRGBPoint(500,1.0,0.5,0.3);
    volumeColor->AddRGBPoint(1000,1.0,0.5,0.3);
    volumeColor->AddRGBPoint(1150,1.0,1.0,0.9);

    // Opacity transfet function is used to control the opacity
    vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity=vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeScalarOpacity->AddPoint(0,0.00);
    volumeScalarOpacity->AddPoint(500,0.15);
    volumeScalarOpacity->AddPoint(1000,0.15);
    volumeScalarOpacity->AddPoint(1150,0.85);

    // For monst medical data, the unit distance is 1mm.
    vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity=vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeGradientOpacity->AddPoint(0,0.0);
    volumeGradientOpacity->AddPoint(90,0.5);
    volumeGradientOpacity->AddPoint(100,1.0);

    // The volumeProperty attaches the color and opacity functions to the volume, and sets other volume properties.
    vtkSmartPointer<vtkVolumeProperty> volumePorperty=vtkSmartPointer<vtkVolumeProperty>::New();
    volumePorperty->SetColor(volumeColor);
    volumePorperty->SetScalarOpacity(volumeScalarOpacity);
    volumePorperty->SetGradientOpacity(volumeGradientOpacity);
    volumePorperty->SetInterpolationTypeToLinear();
    volumePorperty->ShadeOn();
    volumePorperty->SetAmbient(0.3);
    volumePorperty->SetDiffuse(0.8);
    volumePorperty->SetSpecular(0.2);

    // The vtkVolume is a vtkProp3D (like a vtkActor) and controls the position and orientation ofthe volume in world coordinates.
    vtkSmartPointer<vtkVolume> volume=vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumePorperty);
    return volume;
}

vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName){
    vtkSmartPointer<vtkPolyData> polyData;
    string extension=vtksys::SystemTools::GetFilenameExtension(string(fileName));
    if(extension==".ply"){
        vtkSmartPointer<vtkPLYReader> reader=vtkSmartPointer<vtkPLYReader>::New();
        reader->SetFileName(fileName);
        reader->Update();
        polyData=reader->GetOutput();
    }
    else if(extension==".vtp"){
        vtkSmartPointer<vtkXMLPolyDataReader> reader=vtkSmartPointer<vtkXMLPolyDataReader>::New();
        reader->SetFileName(fileName);
        reader->Update();
        polyData=reader->GetOutput();
    }
    else if(extension==".obj"){
        vtkSmartPointer<vtkOBJReader> reader=vtkSmartPointer<vtkOBJReader>::New();
        reader->SetFileName(fileName);
        reader->Update();
        polyData=reader->GetOutput();
    }
    else if(extension==".stl"){
        vtkSmartPointer<vtkSTLReader> reader=vtkSmartPointer<vtkSTLReader>::New();
        reader->SetFileName(fileName);
        reader->Update();
        polyData=reader->GetOutput();
    }
    else{
        vtkSmartPointer<vtkPointSource> pointSource=vtkSmartPointer<vtkPointSource>::New();
        pointSource->SetNumberOfPoints(1000);
        pointSource->SetRadius(1.0);
        pointSource->SetCenter(0,0,0);
        pointSource->SetDistributionToShell();
        pointSource->Update();
        polyData=pointSource->GetOutput();
    }
    return polyData;
}
