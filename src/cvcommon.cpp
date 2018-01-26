#include "cvcommon.h"

void printOutOpenCV_Version(){
    // print out the Opencv Version
    cout<<CV_VERSION<<endl;
}


void extract_features(vector<string> &image_names, vector<vector<KeyPoint> > &key_points_for_all, vector<Mat> &descriptor_for_all, vector<vector<Vec3b> > &colors_for_all){
    // initial vectors
    key_points_for_all.clear();
    descriptor_for_all.clear();
    cv::Mat image;
    // create an ORB detector and extractor.
    cv::Ptr<cv::Feature2D> orb=cv::ORB::create();
    for(vector<string>::const_iterator it=image_names.begin();it!=image_names.end();++it){
        // Read the image into image Mat.
        image=cv::imread(*it,cv::IMREAD_COLOR);
        if(image.empty())
            continue;
        vector<cv::KeyPoint> key_points;
        cv::Mat descriptor;
        // Detect and extract.
        orb->detectAndCompute(image,cv::noArray(),key_points,descriptor);
        // Feature is small , no use the image.
        if(key_points.size()<10)
            continue;
        key_points_for_all.push_back(key_points);
        descriptor_for_all.push_back(descriptor);

        // Do something for color...
        vector<cv::Vec3b> colors(key_points.size());
        for(int i=0;i<key_points.size();++i){
            cv::Point2f& p=key_points[i].pt;
            colors[i]=image.at<cv::Vec3b>(p.y,p.x);
        }
        colors_for_all.push_back(colors);
    }
}

void match_features(Mat &query, Mat &train, vector<DMatch> &matches){
    // We use brute force matcher
    cv::Ptr<cv::DescriptorMatcher> matcher=new cv::BFMatcher(cv::NORM_HAMMING);
    vector<cv::DMatch> bf_matches;
    matcher->match(query,train,bf_matches);
    // --
    double max_dist=0;
    double min_dist=100;
    for(int i=0;i<query.rows;++i){
        double dist=bf_matches[i].distance;
        if(dist<min_dist)
            min_dist=dist;
        if(dist>max_dist)
            max_dist=dist;
    }
    // Good matches
    matches.clear();
    for(int i=0;i<query.rows;++i){
        if(bf_matches[i].distance<=max(3*min_dist,25.0))
            matches.push_back(bf_matches[i]);
    }
}

bool find_transform(Mat &K, vector<Point2f> &p1, vector<Point2f> &p2, Mat &R, Mat &T, Mat &mask){
    // Acquire the focal and pixle plane center.
    double focal_length=0.5*(K.at<double>(0)+K.at<double>(4));
    cv::Point2d principle_point(K.at<double>(2),K.at<double>(5));

    // According to the matched points we can calculate the essenstial matrix. and use ransac to eliminate the outlier.
    cv::Mat E=cv::findEssentialMat(p1,p2,focal_length,principle_point,cv::RANSAC,0.999,1.0,mask);
    if(E.empty())
        return false;

    double feasible_count=cv::countNonZero(mask);
    cout<<(int)feasible_count<<" --in-- "<<p1.size()<<endl;
    // if the ourlier number great than 50%, it's impossible
    if(feasible_count<=15||(feasible_count/p1.size())<0.6)
        return false;

    // decompose the essential matrix to get R and T
    int pass_count=cv::recoverPose(E,p1,p2,R,T,focal_length,principle_point,mask);

    // condition
    if(((double)pass_count)/feasible_count<0.7)
        return false;
    return true;
}


void get_matched_points(vector<KeyPoint> &p1, vector<KeyPoint> &p2, vector<DMatch> matches, vector<Point2f> &out_p1, vector<Point2f> &out_p2){
    //
    out_p1.clear();
    out_p2.clear();
    for(int i=0;i<matches.size();++i){
        out_p1.push_back(p1[matches[i].queryIdx].pt);
        out_p2.push_back(p2[matches[i].trainIdx].pt);
    }
}

void get_matched_colors(vector<Vec3b> &c1, vector<Vec3b> &c2, vector<DMatch> matches, vector<Vec3b> &out_c1, vector<Vec3b> &out_c2){
    //
    out_c1.clear();
    out_c2.clear();
    for(int i=0;i<matches.size();++i){
        out_c1.push_back(c1[matches[i].queryIdx]);
        out_c2.push_back(c2[matches[i].trainIdx]);
    }
}

void reconstruct(Mat &K, Mat &R, Mat &T, vector<Point2f> &p1, vector<Point2f> &p2, Mat &structure){
    // [R T], trianulatePoints can only support float
    cv::Mat proj1(3,4,CV_32FC1);
    cv::Mat proj2(3,4,CV_32FC1);

    proj1(cv::Range(0,3),cv::Range(0,3))=cv::Mat::eye(3,3,CV_32FC1);
    proj1.col(3)=cv::Mat::zeros(3,1,CV_32FC1);

    R.convertTo(proj2(cv::Range(0,3),cv::Range(0,3)),CV_32FC1);
    T.convertTo(proj2.col(3),CV_32FC1);

    cv::Mat float_K;
    K.convertTo(float_K,CV_32FC1);
    proj1=float_K*proj1;
    proj2=float_K*proj2;

    //triangulate
    cv::triangulatePoints(proj1,proj2,p1,p2,structure);
}

void maskout_points(vector<Point2f> &p1, Mat &mask){
    //
    vector<cv::Point2f> p1_copy=p1;
    p1.clear();

    for(int i=0;i<mask.rows;++i){
        if(mask.at<uchar>(i)>0)
            p1.push_back(p1_copy[i]);
    }
}

void maskout_colors(vector<Vec3b> &c1, Mat &mask){
    //
    vector<cv::Vec3b> c1_copy=c1;
    c1.clear();
    for(int i=0;i<mask.rows;++i){
        if(mask.at<uchar>(i)>0)
            c1.push_back(c1_copy[i]);
    }
}

void save_structure(string file_name, vector<Mat> &rotations, vector<Mat> &motions, Mat &structure, vector<Vec3b> &colors){
    // using yaml file format
    int n=(int)rotations.size();

    cv::FileStorage fs(file_name,cv::FileStorage::WRITE);
    fs<<"Camera Count"<<n;
    fs<<"Point Count"<<structure.cols;

    fs<<"Rotations"<<"[";
    for(size_t i=0;i<n;++i){
        fs<<rotations[i];
    }
    fs<<"]";

    fs<<"Motions"<<"[";
    for(size_t i=0;i<n;++i){
        fs<<motions[i];
    }
    fs<<"]";

    fs<<"Points"<<"[";
    for(size_t i=0;i<structure.cols;++i){
        cv::Mat_<float> c=structure.col(i);
        c/=c(3);    //coordinates conversion
        fs<<cv::Point3f(c(0),c(1),c(2));
    }
    fs<<"]";

    fs<<"Colors"<<"[";
    for(size_t i=0;i<colors.size();++i){
        fs<<colors[i];
    }
    fs<<"]";
    fs.release();
}
