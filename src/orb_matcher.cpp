#include "cvcommon.h"
void readme();
int main(int argc,char* argv[]){
    if(argc!=3){
        readme();
        return -1;
    }
    cv::Mat img_object=cv::imread(argv[1],CV_LOAD_IMAGE_COLOR);
    cv::Mat img_scene=cv::imread(argv[2],CV_LOAD_IMAGE_COLOR);
    if(!img_object.data||!img_scene.data){
        cout<<" ---(!) Error reading images"<<endl;
        return -1;
    }

    //-- Step 1: Detect the keypoints using ORB Detector
    //-- Step 2: Calculate descriptors (feature vectors)
    cv::Ptr<Feature2D> orb=cv::ORB::create();
    vector<cv::KeyPoint> keyPoints_object,keyPoints_scene;
    cv::Mat descriptors_object,descriptors_scene;
    orb->detectAndCompute(img_object,cv::noArray(),keyPoints_object,descriptors_object);
    orb->detectAndCompute(img_scene,cv::noArray(),keyPoints_scene,descriptors_scene);
    /*
    for(vector<cv::KeyPoint>::const_iterator it=keyPoints_object.begin();it!=keyPoints_object.end();++it){
        cout<<it->pt<<endl;
    }
    cout<<" Descriptor is a Mat, Mat can be cout."<<endl;
    cout<<descriptors_object<<endl;
    */
    //-- draw keypoints
    //cv::Mat keyPoint_in_Object;
    //cv::drawKeypoints(img_object,keyPoints_object,keyPoint_in_Object);
    //cv::imshow("Key Points in image_object",keyPoint_in_Object);
    //cv::waitKey(0);


    //-- Step 3: Matching descriptor vectors using BruteForce matcher.
    cv::Ptr<DescriptorMatcher> matcher=new cv::BFMatcher(NORM_HAMMING);
    vector<cv::DMatch> matches;
    matcher->match(descriptors_object,descriptors_scene,matches);

    double max_dist=0;double min_dist=100;
    //-- Quick calculation of max and min distance between keypoints
    for(int i=0;i<descriptors_object.rows;i++){
        double dist=matches[i].distance;
        if(dist<min_dist)
            min_dist=dist;
        if(dist>max_dist)
            max_dist=dist;
    }
    cout<<"--Max dist : "<<max_dist<<endl;
    cout<<"--Min dist : "<<min_dist<<endl;


    //-- Draw only "good matches (i.e. whose distance is less than 3*min_dist)
    vector<cv::DMatch> good_matches;
    for(int i=0;i<descriptors_object.rows;++i){
        if(matches[i].distance<=max(3*min_dist,25.0))
            good_matches.push_back(matches[i]);
    }
    cv::Mat img_matches;
    cv::drawMatches(img_object,keyPoints_object,img_scene,keyPoints_scene,good_matches,img_matches,
                    cv::Scalar::all(-1),cv::Scalar::all(-1),vector<char>(),cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    //cv::imshow("good matches",img_matches);
    //cv::waitKey(0);
    /*
    for(vector<cv::DMatch>::const_iterator it=good_matches.begin();it!=good_matches.end();++it){
        cout<<it->queryIdx<<","<<it->trainIdx<<endl;
    }
    */
    //-- Localize the object
    vector<cv::Point2f> obj,scene;
    for(int i=0;i<good_matches.size();++i){
        //-- Get the keypoints from the good matches
        obj.push_back(keyPoints_object[good_matches[i].queryIdx].pt);
        scene.push_back(keyPoints_scene[good_matches[i].trainIdx].pt);
    }
    /*
    // output obj and scene
    fstream out;
    out.open("obj.txt",ios::out);
    if(out.bad()){
        cout<< "Open file error"<<endl;
        return -1;
    }

    for(vector<cv::Point2f>::const_iterator it=obj.begin();it!=obj.end();++it){
        out<<it->x<<" "<<it->y<<endl;
    }
    out.close();
    out.open("scene.txt",ios::out);
    if(out.bad()){
        cout<< "Open file error"<<endl;
        return -1;
    }

    for(vector<cv::Point2f>::const_iterator it=scene.begin();it!=scene.end();++it){
        out<<it->x<<" "<<it->y<<endl;
    }
    out.close();
    */
    cv::Mat H=cv::findHomography(obj,scene,CV_RANSAC);
    cout<<H<<endl;
    return 0;
}

void readme(){
    cout<<" Usage: ./orb_matcher "<<"<image1> <image2>"<<endl;
}
