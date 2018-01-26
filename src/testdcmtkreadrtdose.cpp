#include "dcmtkcommon.h"

int main(int argc,char* argv[]){
    if(argc<2){
        cout<<" Parameter Error"<<" Usage: "<<argv[0]<<"rtdose file."<<endl;
        return -1;
    }
    vtkSmartPointer<vtkImageData> imageData=vtkSmartPointer<vtkImageData>::New();
    getRTDose(imageData,argv[1]);
}
