#include "dcmtkcommon.h"


void getRTPlanBeamISOCenter(double value[3],const char* fileName){
    //
    OFVector<Float64> array;

    //OFVector<Float64> value;
    OFCondition status;
    DcmFileFormat fileformat;
    status=fileformat.loadFile(fileName);
    if(status.good()){
        DRTPlanIOD rtplan;
        status=rtplan.read(*fileformat.getDataset());
        if(status.good()){

            //cout<<"Read rtplan ok."<<endl;
            DRTBeamSequence beamSeq=rtplan.getBeamSequence();
            if(beamSeq.isEmpty()){
                std::cout<<" Error , There is no beamSequence item."<<std::endl;

            }
            status=beamSeq.gotoFirstItem();
            //if(status.good())
                //cout<<" got the first item."<<endl;
            DRTBeamSequence::Item &beamItem=beamSeq.getCurrentItem();
            // ControlPointSequence
            DRTControlPointSequence controlPSeq=beamItem.getControlPointSequence();
            controlPSeq.gotoFirstItem();
            DRTControlPointSequence::Item &cpItem=controlPSeq.getCurrentItem();
            cpItem.getIsocenterPosition(array);
        }
    }
    int i=0;
    for(OFVector<Float64>::const_iterator it=array.begin();it!=array.end();++it){
        value[i]=*it;
        i++;
    }
    // Thanks to the geant4.web.cern.ch/DicomFilePlan.cc source codes.
    // That codes give me the inspiration.
}


void getRTDose(vtkSmartPointer<vtkImageData> imageData,const char* fileName){
    DRTDose rtdose;
    OFCondition status=rtdose.loadFile(fileName);
    if(status.good()){
        const unsigned int frame=0;
        OFVector<double> doseImage;
        status=rtdose.getDoseImage(doseImage,frame);
        if(status.good()){
            //imageData->AllocateScalars(vtkTypeInt16,0);
            OFVector<Float64> pixelSpacing;
            rtdose.getPixelSpacing(pixelSpacing);
            Uint16 w=rtdose.getDoseImageWidth();
            Uint16 h=rtdose.getDoseImageHeight();
            //cout<<w<<","<<h<<endl;
            OFVector<double>::iterator it=doseImage.begin();
            for(Uint16 y=0;y<h;++y){
                for(Uint16 x=0;x<w;++x){
                    double value=*it++;
                    //cout<<value<<endl;
                }
            }


        }




    }
}
