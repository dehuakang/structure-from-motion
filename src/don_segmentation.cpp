#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <pcl/search/organized.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/segmentation/extract_clusters.h>

#include <pcl/features/don.h>

using namespace pcl;
using namespace std;
int main(int argc,char* argv[]){
    // The smallest scale to use in the DoN filter
    double scale1=0.3;
    // The largest scale to use in the DoN filter
    double scale2=4.5;
    // The minimum DoN magnitude to threshold by
    double threshold=0.1;
    // Segment scene into clusters with given distance to lerance using euclidean clustering
    double segradius=1.5;
    if(argc<2){
        cout<<" Usage: "<<argv[0]<<" input file name"<<endl;
        return -1;
    }

    string infile=argv[1];
    // Load cloud in blob format
    pcl::PCLPointCloud2 blob;
    pcl::io::loadPLYFile(infile.c_str(),blob);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>());
    pcl::fromPCLPointCloud2 (blob,*cloud);

    // Create a search tree, use KDTree for non-organized data.
    pcl::search::Search<pcl::PointXYZ>::Ptr tree;
    if(cloud->isOrganized()){
        tree.reset(new pcl::search::OrganizedNeighbor<pcl::PointXYZ>());
    }
    else{
        tree.reset(new pcl::search::KdTree<pcl::PointXYZ>(false));
    }

    // Set the input pointcloud for the search tree
    tree->setInputCloud(cloud);

    if(scale1>=scale2){
        cout<< "Error: Large scale must be > small scale."<<endl;
        return -1;
    }
    // Compute normals using both samll and large scales at each point
    pcl::NormalEstimationOMP<pcl::PointXYZ,pcl::PointNormal> ne;
    ne.setInputCloud(cloud);
    ne.setSearchMethod(tree);
    // Note: set veiwpoint is very important, so that we can ensure normals
    // are all pointed in the same direction.
    ne.setViewPoint(numeric_limits<float>::max(),numeric_limits<float>::max(),numeric_limits<float>::max());

    // Calculate the normal with the small scale
    cout<<" Calculating normals for scale... "<<scale1<<endl;
    pcl::PointCloud<pcl::PointNormal>::Ptr normals_samll_scale (new pcl::PointCloud<pcl::PointNormal>());
    ne.setRadiusSearch(scale1);
    ne.compute(*normals_samll_scale);

    // Calculat normals with the large scale
    cout<<" Calculating normals for scale... "<<scale2<<endl;
    pcl::PointCloud<pcl::PointNormal>::Ptr normals_large_scale (new pcl::PointCloud<pcl::PointNormal>());

    ne.setRadiusSearch(scale2);
    ne.compute(*normals_large_scale);

    // Create output cloud for DoN results
    pcl::PointCloud<pcl::PointNormal>::Ptr doncloud (new pcl::PointCloud<pcl::PointNormal>());
    pcl::copyPointCloud<pcl::PointXYZ,pcl::PointNormal>(*cloud,*doncloud);

    cout<<" Calculating DoN... "<<endl;
    // Create DoN operator
    pcl::DifferenceOfNormalsEstimation<pcl::PointXYZ,pcl::PointNormal,pcl::PointNormal> don;
    don.setInputCloud(cloud);
    don.setNormalScaleLarge(normals_large_scale);
    don.setNormalScaleSmall(normals_samll_scale);

    if(!don.initCompute()){
        cout<<" Error: Could not initialize DoN feature operator"<<endl;
        return -1;
    }
    // Compute DoN
    don.computeFeature(*doncloud);
    // Save Don features
    pcl::PLYWriter writer;
    writer.write<pcl::PointNormal>("don.ply",*doncloud,false);
    // Filter by magnitude
    cout<< "Filtering out DoN mag <= "<<threshold<<"..."<<endl;
    // Build the condition for filtering
    pcl::ConditionOr<pcl::PointNormal>::Ptr range_cond(new
                                                       pcl::ConditionOr<pcl::PointNormal>());
    range_cond->addComparison(pcl::FieldComparison<pcl::PointNormal>::ConstPtr
    (new pcl::FieldComparison<pcl::PointNormal> ("curvature",pcl::ComparisonOps::GT,threshold)));
    // guild the filter
    pcl::ConditionalRemoval<pcl::PointNormal> condrem (range_cond);
    condrem.setInputCloud(doncloud);
    pcl::PointCloud<pcl::PointNormal>::Ptr doncloud_filtered (new pcl::PointCloud<pcl::PointNormal>());

    // Apply filter
    condrem.filter(*doncloud_filtered);
    doncloud=doncloud_filtered;
    // Save filtered output
    cout<<" Filtered Pointcloud: "<<doncloud->points.size()<<" data points."<<endl;
    writer.write<pcl::PointNormal>("don_filtered.ply",*doncloud,false);

    // filter by magnitude
    cout<<" Clustering using EuclideanClusterExtraction with tolerance <= "<<segradius<<"..."<<endl;
    pcl::search::KdTree<pcl::PointNormal>::Ptr segtree (new pcl::search::KdTree<pcl::PointNormal>());
    segtree->setInputCloud(doncloud);

    vector<pcl::PointIndices> cluster_indices;
    pcl::EuclideanClusterExtraction<pcl::PointNormal> ec;

    ec.setClusterTolerance(segradius);
    ec.setMinClusterSize(15);
    ec.setMaxClusterSize(100);
    ec.setSearchMethod(segtree);
    ec.setInputCloud(doncloud);
    ec.extract(cluster_indices);

    int j=0;
    for(vector<pcl::PointIndices>::const_iterator it=cluster_indices.begin();it!=cluster_indices.end();++it,j++){
        pcl::PointCloud<pcl::PointNormal>::Ptr cloud_cluster_don (new pcl::PointCloud<pcl::PointNormal>());
        for(vector<int>::const_iterator pit=it->indices.begin();pit!=it->indices.end();++pit){
            cloud_cluster_don->points.push_back(doncloud->points[*pit]);
        }
        cloud_cluster_don->width=int(cloud_cluster_don->points.size());
        cloud_cluster_don->height=1;
        cloud_cluster_don->is_dense=true;
        // Save cluster
        cout<< "PointCloud representing the Cluster: "<<cloud_cluster_don->points.size()<<" data points."<<endl;
        stringstream ss;
        ss<<"don_cluster_"<<j<<".ply";
        writer.write<pcl::PointNormal>(ss.str(),*cloud_cluster_don,false);
    }

    return 0;
}

