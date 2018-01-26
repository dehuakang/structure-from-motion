#include "dcmtkcommon.h"

int main(int argc,char* argv[]){
    //
    if(argc<2){
        std::cout<<" Error -- Usage: "<<argv[0]<<"rtplan file"<<std::endl;
        return -1;
    }
    double a[3];
    getRTPlanBeamISOCenter(a,argv[1]);
    std::cout<<a[0]<<","<<a[1]<<","<<a[2]<<std::endl;


    return 0;
}
