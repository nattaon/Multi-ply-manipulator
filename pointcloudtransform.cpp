#include "pointcloudtransform.h"
#include <iostream>
PointcloudTransform::PointcloudTransform()
{
    //pointcloud initialize
    pointcloud.reset(new PointCloudXYZRGB);
}

bool PointcloudTransform::loadPLY(QString filename)// load to PointCloudXYZRGB::Ptr pointcloud
{
    if (filename.isEmpty ())
      return false;

    int return_status = pcl::io::loadPLYFile (filename.toStdString(), *pointcloud);
    if (return_status != 0)
      {
        PCL_ERROR("Error reading point cloud %s\n", filename.toStdString().c_str());
        return false;
      }
    return true;
}

bool PointcloudTransform::savePLY(QString filename)// save PointCloudXYZRGB::Ptr pointcloud
{
    if (filename.isEmpty ())
      return false;

    int return_status;

    if (filename.endsWith (".ply", Qt::CaseInsensitive))
      return_status = pcl::io::savePLYFileBinary (filename.toStdString (), *pointcloud);
    else
    {
      filename.append(".ply");
      return_status = pcl::io::savePLYFileBinary (filename.toStdString (), *pointcloud);
    }

    if (return_status != 0)
    {
      PCL_ERROR("Error writing point cloud %s\n", filename.toStdString ().c_str ());
      return false;
    }
    return true;
}


PointCloudXYZRGB::Ptr PointcloudTransform::GetRawPointCloud()
{
    return pointcloud;
}

int PointcloudTransform::GetRawPLYSize()
{
    return pointcloud->points.size();

}

void PointcloudTransform::ApplyRotation(double rotate_angle, Eigen::Matrix<float, 1, 3>  rotation_axis)
{
    Eigen::Affine3f transform = Eigen::Affine3f::Identity();
    transform.rotate(Eigen::AngleAxisf(rotate_angle*M_PI/180, rotation_axis));
    pcl::transformPointCloud(*pointcloud, *pointcloud, transform);
}

void PointcloudTransform::ApplyPlaneSegmentation(double planeinlier_threshold)
{
    //PointCloudXYZRGB::Ptr before_applyplane_cloud;
    //pcl::copyPointCloud(*pointcloud, *before_applyplane_cloud);

    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);

    // 1. find pointclouds index(inlier) which is locate in plane
    pcl::SACSegmentation<PointTypeXYZRGB> seg;
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(planeinlier_threshold);
    seg.setInputCloud(pointcloud);
    seg.segment(*inliers, *coefficients);

    //coefficients : 4 : -0.00855 -0.997799 0.0657631 -3.58483
    std::cout << "coefficients : "<< coefficients->values.size()  << " : " << coefficients->values[0] << " " << coefficients->values[1] << " " << coefficients->values[2] <<  " " << coefficients->values[3] << std::endl;

    // 2. extract plane and not plane pointcloud from inlier
    pcl::ExtractIndices<pcl::PointXYZRGB> extract;
    extract.setInputCloud(pointcloud);
    extract.setIndices(inliers);

    extract.setNegative(true);
    extract.filter(*pointcloud);
}

