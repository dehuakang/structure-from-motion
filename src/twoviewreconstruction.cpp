#include "cvcommon.h"

int main(int argc,char* argv[]){
    if(argc<3){
        cout<<"Usage : "<<argv[0]<<" file1 file2 "<<endl;
        return -1;
    }
    vector<string> img_names={string(argv[1]),string(argv[2])};
    vector<vector<cv::KeyPoint>> keypoints_for_all;
    vector<cv::Mat> descriptor_for_all;
    vector<vector<cv::Vec3b>> colors_for_all;
    vector<cv::DMatch> matches;

    // Essential Matrix
    cv::Mat K(cv::Matx33d(2759.48,0,1520.69,
                          0,2764.16,1006.81,
                          0,0,1));
    // Extract features
    extract_features(img_names,keypoints_for_all,descriptor_for_all,colors_for_all);
    // Match features
    match_features(descriptor_for_all[0],descriptor_for_all[1],matches);
    /* print the matches to verify the results.
    for(vector<cv::DMatch>::const_iterator it=matches.begin();it!=matches.end();++it){
        cout<<it->queryIdx<<","<<it->trainIdx<<endl;
    }
    */
    // Compute the transform matrix
    vector<cv::Point2f> p1,p2;
    vector<cv::Vec3b> c1,c2;
    cv::Mat R,T;
    cv::Mat mask;
    get_matched_points(keypoints_for_all[0],keypoints_for_all[1],matches,p1,p2);
    get_matched_colors(colors_for_all[0],colors_for_all[1],matches,c1,c2);
    find_transform(K,p1,p2,R,T,mask);

    // Reconstruct
    cv::Mat structure;  //4 rows N cols
    maskout_points(p1,mask);
    maskout_points(p2,mask);
    reconstruct(K,R,T,p1,p2,structure);
    //
    //cout<<structure<<endl;
    //printOutOpenCV_Version();
    vector<cv::Mat> rotations={cv::Mat::eye(3,3,CV_64FC1),R};
    vector<cv::Mat> motions={cv::Mat::zeros(3,1,CV_64FC1),T};
    maskout_colors(c1,mask);
    save_structure("structure.yml",rotations,motions,structure,c1);
    return 0;
}
