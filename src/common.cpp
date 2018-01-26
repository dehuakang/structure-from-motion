#include "common.h"


vtkSmartPointer<vtkActor> createOrigin(){
    // Create an original point which sits on the [0,0,0] point
    vtkSmartPointer<vtkActor> actor=vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPoints> points=vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0,0,0);
    vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter=vtkSmartPointer<vtkVertexGlyphFilter>::New();
    vtkSmartPointer<vtkPolyData> polydata=vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);
    vertexFilter->SetInputData(polydata);
    vertexFilter->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(vertexFilter->GetOutputPort());

    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1,0,0);
    actor->GetProperty()->SetPointSize(8);
    return actor;
}

vtkSmartPointer<vtkActor> createPoint(){
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

void DisplayNamedColorNames(vtkSmartPointer<vtkNamedColors> colors){
    // Display NamedColors name.
    vector<string> colorName;
    for(int i=0;i<colors->GetNumberOfColors();++i){
        colorName.push_back(colors->GetColorNames());
    }
    for(vector<string>::const_iterator it=colorName.begin();it!=colorName.end();++it){
        cout<<"---------------------------------\n        "<<*it<<endl;
    }
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

vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName){
    // Read polyData. if there is no input ,it can create a points distribution.
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
        polyData->ShallowCopy(reader->GetOutput());
    }
    else{
        // Create a point set source.
        vtkSmartPointer<vtkPointSource> points=vtkSmartPointer<vtkPointSource>::New();
        points->SetNumberOfPoints(1500);
        points->SetRadius(10.0);
        points->SetCenter(vtkMath::Random(-10,10),
                          vtkMath::Random(-10,10),
                          vtkMath::Random(-10,10));
        points->SetDistributionToShell();
        points->Update();
        polyData=points->GetOutput();
    }
    return polyData;
}


vtkSmartPointer<vtkPolyDataAlgorithm> MakeExtractSurface(vtkPolyData *polyData){
    //
    double bounds[6];
    polyData->GetBounds(bounds);
    double range[3];
    for(int i=0;i<3;++i){
        range[i]=bounds[2*i+1]-bounds[2*i];
    }

    int sampleSize=polyData->GetNumberOfPoints()*0.00005;
    if(sampleSize<10){
        sampleSize=50;
    }

    // Do we need to estimante normals?
    vtkSmartPointer<vtkSignedDistance> distance=vtkSmartPointer<vtkSignedDistance>::New();
    if(polyData->GetPointData()->GetNormals()){
        cout<<"ExtractSurface: Using normal from input file"<<endl;
        distance->SetInputData(polyData);
    }
    else{
        cout<<"ExtractSurface: Estimating normals using PCANormalEstimation"<<endl;
        vtkSmartPointer<vtkPCANormalEstimation> normals=vtkSmartPointer<vtkPCANormalEstimation>::New();
        normals->SetInputData(polyData);
        normals->SetSampleSize(sampleSize);
        normals->SetNormalOrientationToGraphTraversal();
        normals->FlipNormalsOn();
        distance->SetInputConnection(normals->GetOutputPort());
    }

    int dimension=256;
    double radius;
    radius=max(max(range[0],range[1]),range[2])/static_cast<double>(dimension)*4;   //~4 voxels

    distance->SetRadius(radius);
    distance->SetDimensions(dimension,dimension,dimension);
    distance->SetBounds(
                bounds[0]-range[0]*0.1,
                bounds[1]+range[0]*0.1,
                bounds[2]-range[1]*0.1,
                bounds[3]+range[1]*0.1,
                bounds[4]-range[2]*0.1,
                bounds[5]+range[2]*0.1);

    vtkSmartPointer<vtkExtractSurface> surface=vtkSmartPointer<vtkExtractSurface>::New();
    surface->SetInputConnection(distance->GetOutputPort());
    surface->SetRadius(radius*.99);
    return surface;
}

vtkSmartPointer<vtkPolyData> MakeMarchingCubeExractSurface(const char *folderName){
    // Reade a series dicom files in a folder
    vtkSmartPointer<vtkDICOMImageReader> dicomReader=vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomReader->SetDirectoryName(folderName);
    dicomReader->Update();
    double ImagePositionPatient[3];
    ImagePositionPatient[0]=dicomReader->GetImagePositionPatient()[0];
    ImagePositionPatient[1]=-dicomReader->GetImagePositionPatient()[1];
    ImagePositionPatient[2]=-dicomReader->GetImagePositionPatient()[2];
    ImagePositionPatient[1]-=(dicomReader->GetDataExtent()[3])*dicomReader->GetPixelSpacing()[1];
    ImagePositionPatient[2]-=(dicomReader->GetDataExtent()[5])*dicomReader->GetPixelSpacing()[2];

    // Create a 3D model using marching cubes
    vtkSmartPointer<vtkMarchingCubes> mc=vtkSmartPointer<vtkMarchingCubes>::New();
    mc->SetInputConnection(dicomReader->GetOutputPort());
    mc->ComputeNormalsOn();
    mc->ComputeGradientsOn();
    mc->SetValue(0,100);   //second value acts as threshold.

    // To remain largest region
    vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter=vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
    confilter->SetInputConnection(mc->GetOutputPort());
    //confilter->SetExtractionModeToLargestRegion();
    confilter->SetExtractionModeToAllRegions();

    vtkSmartPointer<vtkTransform> originalTransform=vtkSmartPointer<vtkTransform>::New();
    originalTransform->Translate(ImagePositionPatient);
    vtkSmartPointer<vtkTransformFilter> filter=vtkSmartPointer<vtkTransformFilter>::New();
    filter->SetTransform(originalTransform);
    filter->SetInputConnection(confilter->GetOutputPort());
    filter->Update();
    vtkSmartPointer<vtkPolyData> polyData=vtkSmartPointer<vtkPolyData>::New();
    polyData->ShallowCopy(filter->GetOutput());
    return polyData;
}


vtkSmartPointer<vtkVolume> readDICOMreturnVolume(const char *folderName){
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

bool GetPointNormals(vtkSmartPointer<vtkPolyData> polydata){
    cout<<" In GetPointNormals: "<<polydata->GetNumberOfPoints()<<endl;
    cout<<" Looking for point normals..."<<endl;

    // Count points
    vtkIdType numPoints=polydata->GetNumberOfPoints();
    cout<<" There are "<<numPoints<<" points."<<endl;

    // Count triangles
    vtkIdType numPolys=polydata->GetNumberOfPolys();
    cout<<" There are "<<numPolys<<" polys."<<endl;

    // Double normals in an array
    vtkSmartPointer<vtkDoubleArray> normalDataDouble=vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetArray("Normals"));
    if(normalDataDouble){
        int nc=normalDataDouble->GetNumberOfTuples();
        cout<<"There are "<<nc<<" components in normalDataDouble"<<endl;
        return true;
    }
    // Float normals in an array
    vtkSmartPointer<vtkFloatArray> normalDataFloat=vtkFloatArray::SafeDownCast(polydata->GetPointData()->GetArray("Normals"));
    if(normalDataFloat){
        int nc=normalDataFloat->GetNumberOfTuples();
        cout<<"There are "<<nc<<" components in normalDataFloat"<<endl;
        return true;
    }
    // Point normals
    vtkSmartPointer<vtkDoubleArray> normalsDouble=vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetNormals());
    if(normalsDouble){
        cout<<" There are "<<normalsDouble->GetNumberOfComponents()<<" components in normalsDouble."<<endl;
        return true;
    }
    vtkSmartPointer<vtkFloatArray> normalsFloat=vtkFloatArray::SafeDownCast(polydata->GetPointData()->GetNormals());
    if(normalsFloat){
        cout<<" There are "<<normalsFloat->GetNumberOfComponents()<<" components in normalsFloat."<<endl;
        return true;
    }
    // Generic type point normals
    vtkSmartPointer<vtkDataArray> normalsGeneric=polydata->GetPointData()->GetNormals();
    if(normalsGeneric){
        cout<<" There are "<<normalsGeneric->GetNumberOfTuples()<<" normals in nomalsGeneric."<<endl;
        double testDouble[3];
        normalsGeneric->GetTuple(0,testDouble);
        cout<<" Double: "<<testDouble[0]<<","<<testDouble[1]<<","<<testDouble[2]<<endl;
        return true;
    }
    cout<<" Normals not found."<<endl;
    return false;
}

bool GetCellNormals(vtkSmartPointer<vtkPolyData> polydata){
    cout<<" Looking for cell normals..."<<endl;

    // Count points
    vtkIdType numCells=polydata->GetNumberOfCells();
    cout<<"There are "<<numCells<<" cells."<<endl;

    // Count triangles
    vtkIdType numPolys=polydata->GetNumberOfPolys();
    cout<<"There are "<<numPolys<<" polys."<<endl;

    // Double normals in an array
    vtkSmartPointer<vtkDataArray> normalDataDouble=
            vtkDoubleArray::SafeDownCast(polydata->GetCellData()->GetArray("Normals"));
    if(normalDataDouble){
        int nc=normalDataDouble->GetNumberOfTuples();
        cout<<"There are "<<nc<<" components in normalDataDouble."<<endl;
        return true;
    }
    // Float normals in an array
    vtkSmartPointer<vtkFloatArray> normalDataFloat=
            vtkFloatArray::SafeDownCast(polydata->GetCellData()->GetArray("Normals"));
    if(normalDataFloat){
        int nc=normalDataFloat->GetNumberOfTuples();
        cout<<"There are "<<nc<<" components in normalDataFloat."<<endl;
        return true;
    }

    // Point normals in double
    vtkSmartPointer<vtkDataArray> normalsDouble=
            vtkDataArray::SafeDownCast(polydata->GetCellData()->GetNormals());
    if(normalsDouble){
        cout<<"There are "<<normalsDouble->GetNumberOfComponents()<<" components in normalsDouble."<<endl;
        return true;
    }
    // Point normals in float
    vtkSmartPointer<vtkFloatArray> normalsFloat=
            vtkFloatArray::SafeDownCast(polydata->GetCellData()->GetNormals());
    if(normalsFloat){
        cout<<"There are "<<normalsFloat->GetNumberOfComponents()<<" components in normalsFloat."<<endl;
        return true;
    }
    // Generic type point normals
    vtkSmartPointer<vtkDataArray> normalsGeneric=polydata->GetCellData()->GetNormals();
    if(normalsGeneric){
        cout<<"There are "<<normalsGeneric->GetNumberOfTuples()<<" components in normalsGeneric."<<endl;
        double testDouble[3];
        normalsGeneric->GetTuple(0,testDouble);
        cout<<"Double : "<<testDouble[0]<<","<<testDouble[1]<<","<<testDouble[2]<<endl;
        return true;
    }
    cout<<"Normals not found!"<<endl;
    return false;
}


void TestPointNormals(vtkSmartPointer<vtkPolyData> polydata){
    cout<<" In TestPointNormals: "<<polydata->GetNumberOfPoints()<<endl;
    // Try to read normals directly
    bool hasPointNormals=GetPointNormals(polydata);
    if(!hasPointNormals){
        cout<<" No point normals were found. Computing normals..."<<endl;
        //Generate normals
        vtkSmartPointer<vtkPolyDataNormals> normalGenerator=vtkSmartPointer<vtkPolyDataNormals>::New();
        normalGenerator->SetInputData(polydata);
        normalGenerator->ComputePointNormalsOn();
        normalGenerator->ComputeCellNormalsOff();
        normalGenerator->Update();
        /*
        // Optional settings
        normalGenerator->SetFeatureAngle(0.1);
        normalGenerator->SetSplitting(1);
        normalGenerator->SetConsistency(0);
        normalGenerator->SetAutoOrientNormals(0);
        normalGenerator->SetComputePointNormals(1);
        normalGenerator->SetComputeCellNormals(0);
        normalGenerator->SetFlipNormals(0);
        normalGenerator->SetNonManifoldTraversal(1);
        */
        polydata=normalGenerator->GetOutput();
        //Try to read normals again
        hasPointNormals=GetPointNormals(polydata);
        cout<<" On the 2nd try, has point normals? "<<hasPointNormals<<endl;
    }
    else{
        cout<<"Point normals were found! "<<endl;
    }


}

void TestCellNormals(vtkSmartPointer<vtkPolyData> polydata){
    // Try to read normals directly
    bool hasCellNormals=GetCellNormals(polydata);
    if(!hasCellNormals){
        cout<<" No cell normals were found. Computing normals..."<<endl;
        //Generate normals
        vtkSmartPointer<vtkPolyDataNormals> normalGenerator=vtkSmartPointer<vtkPolyDataNormals>::New();
        normalGenerator->SetInputData(polydata);
        normalGenerator->ComputePointNormalsOff();
        normalGenerator->ComputeCellNormalsOn();
        normalGenerator->Update();
        /*
        // Optional settings
        normalGenerator->SetFeatureAngle(0.1);
        normalGenerator->SetSplitting(1);
        normalGenerator->SetConsistency(0);
        normalGenerator->SetAutoOrientNormals(0);
        normalGenerator->SetComputePointNormals(1);
        normalGenerator->SetComputeCellNormals(0);
        normalGenerator->SetFlipNormals(0);
        normalGenerator->SetNonManifoldTraversal(1);
        */
        polydata=normalGenerator->GetOutput();
        //Try again
        hasCellNormals=GetCellNormals(polydata);
        cout<<" On the 2nd try, has cell normals? "<<hasCellNormals<<endl;
    }
    else{
        cout<<"Cell normals were found!"<<endl;
    }

}
