#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/registration/ndt.h>
#include <pcl/filters/approximate_voxel_grid.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>

typedef pcl::PointCloud<pcl::PointXYZ> pointCloud;

int main(int argc,char* argv[]){
    if(argc<3){
        cout<<" Usage : "<<argv[0]<<"file1.pcd file2.pcd"<<endl;
        return -1;
    }

    pointCloud::Ptr target_cloud (new pointCloud);
    // Loading first scan of source.
    if(pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1],*target_cloud)==-1){
        PCL_ERROR(" Could not read file \n");
        return -1;
    }
    std::cout<<"Load "<<target_cloud->size()<<" data points from "<<argv[1]<<std::endl;
    // Loading second scan of scene.
    pointCloud::Ptr input_cloud (new pointCloud);
    if(pcl::io::loadPCDFile<pcl::PointXYZ>(argv[2],*input_cloud)==-1){
        PCL_ERROR(" Could not read file \n");
        return -1;
    }
    std::cout<<" Load "<<input_cloud->size()<<" data points from "<<argv[2]<<std::endl;

    // Filtering input scan
    pointCloud::Ptr filtered_cloud (new pointCloud);
    pcl::ApproximateVoxelGrid<pcl::PointXYZ> approximate_voxel_filter;
    approximate_voxel_filter.setLeafSize(0.2,0.2,0.2);
    approximate_voxel_filter.setInputCloud(input_cloud);
    approximate_voxel_filter.filter(*filtered_cloud);
    std::cout<<" Filtered cloud contains "<<filtered_cloud->size()
            <<" data points from "<<argv[2]<<std::endl;

    // Initializing Normal Distributions Transform (NDT).
    pcl::NormalDistributionsTransform<pcl::PointXYZ,pcl::PointXYZ> ndt;
    // Setting scale dependent NDT parameters
    // Setting minimum transformation difference for termination condition.
    ndt.setEuclideanFitnessEpsilon(0.01);
    // Setting maximin step size for more-Thuente line search.
    ndt.setStepSize(0.1);
    // Setting resolution.
    ndt.setResolution(1.0);
    // Setting max number of registration iterations.
    ndt.setMaximumIterations(35);

    ndt.setInputSource(filtered_cloud);
    ndt.setInputTarget(target_cloud);
    //
    Eigen::AngleAxisf init_rotation (0.6931,Eigen::Vector3f(0,0,1));
    Eigen::Translation3f init_translation(1.79387,0.720047,0);
    Eigen::Matrix4f init_guess=(init_translation*init_rotation).matrix();

    pointCloud::Ptr output_cloud (new pointCloud);
    ndt.align(*output_cloud,init_guess);
    std::cout<<"Normal Distributions Transform has converged: "<<ndt.hasConverged()
            <<" Score: "<<ndt.getFitnessScore()
           <<" Number of iterations : "<<ndt.getFinalNumIteration()<<std::endl;

    // transform
    pcl::transformPointCloud(*input_cloud,*output_cloud,ndt.getFinalTransformation());

    // visualizer
    boost::shared_ptr<pcl::visualization::PCLVisualizer>
            viewer_final (new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer_final->setBackgroundColor(0,0,0);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
            target_color (target_cloud,255,0,0);
    viewer_final->addPointCloud<pcl::PointXYZ> (target_cloud,target_color,"target cloud");
    viewer_final->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,1,"target cloud");

    //
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
            output_color (output_cloud,0,255,0);
    viewer_final->addPointCloud<pcl::PointXYZ> (output_cloud,output_color,"output cloud");
    viewer_final->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,1,"output cloud");

    //
    //viewer_final->addCoordinateSystem(1.0,"3D Viewer");
    viewer_final->initCameraParameters();
    while(!viewer_final->wasStopped()){
        viewer_final->spinOnce();
        //boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }
    return 0;
}

