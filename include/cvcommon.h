#ifndef CVCOMMON_H
#define CVCOMMON_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;
using namespace cv;

void printOutOpenCV_Version();

void extract_features(vector<string>& image_names,
                      vector<vector<cv::KeyPoint>>& key_points_for_all,
                      vector<cv::Mat>& descriptor_for_all,
                      vector<vector<cv::Vec3b>>& colors_for_all);

void match_features(cv::Mat& query,cv::Mat& train,vector<cv::DMatch>& matches);

bool find_transform(cv::Mat& K,vector<cv::Point2f>& p1,vector<cv::Point2f>& p2,
                    cv::Mat& R,cv::Mat& T,cv::Mat& mask);

void get_matched_points(vector<cv::KeyPoint>& p1,
                        vector<cv::KeyPoint>& p2,
                        vector<cv::DMatch> matches,
                        vector<cv::Point2f>& out_p1,
                        vector<cv::Point2f>& out_p2);
void get_matched_colors(vector<cv::Vec3b>& c1,
                        vector<cv::Vec3b>& c2,
                        vector<cv::DMatch> matches,
                        vector<cv::Vec3b>& out_c1,
                        vector<cv::Vec3b>& out_c2);

void reconstruct(cv::Mat& K,cv::Mat& R,cv::Mat& T,
                 vector<cv::Point2f>& p1,vector<cv::Point2f>& p2,cv::Mat& structure);

void maskout_points(vector<cv::Point2f>& p1,cv::Mat& mask);
void maskout_colors(vector<cv::Vec3b>& c1,cv::Mat& mask);

void save_structure(string file_name,vector<cv::Mat>& rotations,vector<cv::Mat>& motions,
                    cv::Mat& structure,vector<cv::Vec3b>& colors);

#endif // CVCOMMON

