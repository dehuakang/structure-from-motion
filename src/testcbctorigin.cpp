#include "common.h"




int main(int argc,char* argv[]){
    if(argc<2){
        cout<<" Error, Usage : "<<argv[0]<<" dicom files dir"<<endl;
        return -1;
    }
    vtkSmartPointer<vtkNamedColors> colors=vtkSmartPointer<vtkNamedColors>::New();
    vtkSmartPointer<vtkPolyData> polydata=MakeMarchingCubeExractSurface(argv[1]);
    //double a[3];
    //getRTPlanBeamISOCenter(a,argv[2]);
    vtkSmartPointer<vtkTransform> trans=vtkSmartPointer<vtkTransform>::New();
    trans->Translate(0,-106.176,0);
    vtkSmartPointer<vtkTransformPolyDataFilter> transFilter=vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    transFilter->SetTransform(trans);
    transFilter->SetInputData(polydata);
    transFilter->Update();


    // Write it to ply file,befor write it must be converted to polydata
    // if use transformpolydatafilter, below is useless.
    vtkSmartPointer<vtkCleanPolyData> clean=vtkSmartPointer<vtkCleanPolyData>::New();
    clean->SetInputConnection(transFilter->GetOutputPort());
    clean->Update();
    //TestPointNormals(clean->GetOutput());
    //TestCellNormals(clean->GetOutput());

    vtkSmartPointer<vtkArrowSource> arrow=vtkSmartPointer<vtkArrowSource>::New();
    // Add cell normal to the polydata.
    vtkSmartPointer<vtkPolyDataNormals> normalGenerator=vtkSmartPointer<vtkPolyDataNormals>::New();
    normalGenerator->SetInputConnection(transFilter->GetOutputPort());
    //normalGenerator->ComputePointNormalsOn();
    //normalGenerator->ComputeCellNormalsOn();
    normalGenerator->Update();
    vtkSmartPointer<vtkPolyData> poly=normalGenerator->GetOutput();
    TestPointNormals(poly);
    //TestCellNormals(poly);

    //writePLYFileUsePolyData(clean->GetOutput(),"search_sphere.ply");
    vtkSmartPointer<vtkGlyph3D> glyphs=vtkSmartPointer<vtkGlyph3D>::New();
    glyphs->SetSourceConnection(arrow->GetOutputPort());
    glyphs->SetInputConnection(transFilter->GetOutputPort());
    glyphs->ScalingOn();
    glyphs->SetScaleModeToScaleByVector();
    glyphs->SetScaleFactor(0.025);
    glyphs->OrientOn();
    glyphs->ClampingOff();
    glyphs->SetVectorModeToUseVector();
    glyphs->SetIndexModeToOff();
    vtkSmartPointer<vtkPolyDataMapper> glyphMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    glyphMapper->SetInputConnection(glyphs->GetOutputPort());
    glyphMapper->ScalarVisibilityOff();
    vtkSmartPointer<vtkActor> glyphActor=vtkSmartPointer<vtkActor>::New();
    glyphActor->SetMapper(glyphMapper);

    // Curvature
    vtkSmartPointer<vtkCurvatures> curvaturesFilter=vtkSmartPointer<vtkCurvatures>::New();
    curvaturesFilter->SetInputData(poly);
    //curvaturesFilter->SetCurvatureTypeToMinimum();
    //curvaturesFilter->SetCurvatureTypeToMaximum();
    curvaturesFilter->SetCurvatureTypeToGaussian();
    //curvaturesFilter->SetCurvatureTypeToMean();
    curvaturesFilter->Update();

    // Get Scalar range from computed curvature.
    double scalarRange[2];
    curvaturesFilter->GetOutput()->GetScalarRange(scalarRange);
    // Create LookupTable
    vtkSmartPointer<vtkLookupTable> lut=vtkSmartPointer<vtkLookupTable>::New();
    lut->SetHueRange(0.0,0.6);
    lut->SetAlphaRange(1.0,1.0);
    lut->SetValueRange(1.0,1.0);
    lut->SetSaturationRange(1.0,1.0);
    lut->SetNumberOfTableValues(256);
    lut->SetRange(scalarRange);
    lut->Build();
    //cout<<scalarRange[0]<<","<<scalarRange[1]<<endl;

    /*
    int scheme=16;
    // Build a lookup table.
    vtkSmartPointer<vtkColorSeries> colorSeries=vtkSmartPointer<vtkColorSeries>::New();
    colorSeries->SetColorScheme(scheme);
    cout<<" Using color scheme #: "<<colorSeries->GetColorScheme()<<" is "
       <<colorSeries->GetColorSchemeName()<<endl;
    vtkSmartPointer<vtkColorTransferFunction> lut=vtkSmartPointer<vtkColorTransferFunction>::New();
    lut->SetColorSpaceToHSV();
    // Use a color series to create a transfer function
    int numColors=colorSeries->GetNumberOfColors();
    for(int i=0;i<numColors;++i){

        vtkColor3ub color=colorSeries->GetColor(i);
        double dColor[3];
        dColor[0]=static_cast<double>(color[0])/255.0;
        dColor[1]=static_cast<double>(color[1])/255.0;
        dColor[2]=static_cast<double>(color[2])/255.0;
        double t=scalarRange[0]+(scalarRange[1]-scalarRange[0])/(numColors-1)*i;
        lut->AddRGBPoint(t,dColor[0],dColor[1],dColor[2]);
    }
    */
    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    //mapper->SetInputConnection(curvaturesFilter->GetOutputPort());
    mapper->SetInputData(curvaturesFilter->GetOutput());

    mapper->SetLookupTable(lut);
    //mapper->SetScalarRange(scalarRange);  //Do not use it if you used the SetLookupTable function.



    vtkSmartPointer<vtkActor> actor=vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    //actor->GetProperty()->SetColor(colors->GetColor3d("green").GetData());
    actor->GetProperty()->SetOpacity(0.4);
    vtkSmartPointer<vtkActor> originActor=createOrigin();
    vtkSmartPointer<vtkScalarBarActor> scalarBar=vtkSmartPointer<vtkScalarBarActor>::New();
    scalarBar->SetLookupTable(mapper->GetLookupTable());
    scalarBar->SetTitle(curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetName());
    scalarBar->SetNumberOfLabels(10);

    vtkSmartPointer<vtkRenderer> render=vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow=vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style=vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);

    render->AddActor(actor);
    //render->AddActor(originActor);
    render->AddActor2D(scalarBar);
    //render->AddActor(glyphActor);
    renderWindow->AddRenderer(render);
    renderWindow->SetSize(800,800);
    iren->SetRenderWindow(renderWindow);
    iren->Initialize();
    iren->Start();
    return 0;
}
