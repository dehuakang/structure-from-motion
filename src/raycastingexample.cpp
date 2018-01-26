#include "vtkcommon.h"

int main(int argc,char* argv[]){
    if(argc<2){
        cout<<" Usage : "<<argv[0]<<" dicom dir"<<endl;
        return -1;
    }
    vtkSmartPointer<vtkVolume> volume=ReadDICOMreturnVolume(argv[1]);
    vtkSmartPointer<vtkRenderer> ren=vtkSmartPointer<vtkRenderer>::New();
    ren->AddViewProp(volume);

    vtkSmartPointer<vtkRenderWindow> renWin=vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren);
    renWin->SetSize(600,600);

    vtkSmartPointer<vtkRenderWindowInteractor> iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style=vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);
    iren->SetRenderWindow(renWin);
    iren->Start();
    return 0;
}
