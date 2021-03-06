#ifndef POINTCLOUDTRANSFORM_H
#define POINTCLOUDTRANSFORM_H

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/png_io.h>
#include <pcl/io/point_cloud_image_extractors.h>

#include <pcl/common/common_headers.h>
#include <pcl/common/common.h>
#include <pcl/common/io.h>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>
#include <pcl/correspondence.h>
#include <pcl/ModelCoefficients.h>

#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_plane.h>

#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/passthrough.h>

#include <pcl/features/moment_of_inertia_estimation.h>

#include <QObject>
typedef pcl::PointXYZ PointTypeXYZ;
typedef pcl::PointXYZRGB PointTypeXYZRGB;
typedef pcl::PointCloud<PointTypeXYZRGB> PointCloudXYZRGB;
typedef pcl::PointCloud<pcl::PointXYZ> PointCloudXYZ;

class PointcloudTransform
{
public:
    PointcloudTransform();
    bool loadPLY(QString filename);
    void ReloadPLY();
    bool savePLY(QString filename);
    int GetRawPLYSize();
    PointCloudXYZRGB::Ptr GetRawPointCloud();
    void ApplyRotation(double rotate_angle, Eigen::Matrix<float, 1, 3>  rotation_axis);

    void ApplyPlaneSegmentation(double planeinlier_threshold);
    std::vector<int> ApplyPlaneSegmentationWithParameter(double planeinlier_threshold, Eigen::Vector4f plane_coef);
    void ApplyPlaneSegmentationWithInlierPointcloud(double planeinlier_threshold);

    pcl::ModelCoefficients::Ptr GetPlaneSegmentationParameter(double planeinlier_threshold);
    void PlaneSegmentation1(double planeinlier_threshold);
    void PlaneSegmentation2(double planeinlier_threshold);



    void FilterVoxelSize(double size);
    void StatisticalOutlierRemoval(int meank, double stddev);
    Eigen::Vector3f CalculateMassCenter();
    Eigen::Vector3f CalculateMassCenterVoxel(double size);
    void MovePointCloudFromTo(PointTypeXYZRGB current_pos, PointTypeXYZRGB target_pos);
    void PassthroughFilter(std::string axis, float min, float max);
    void GetBounding(PointTypeXYZRGB &minpoint, PointTypeXYZRGB &maxpoint);
    void SavePointCloudImage(std::string filename);
    void PointcloudAlignAxis();

    PointTypeXYZRGB min_point_AABB;
    PointTypeXYZRGB max_point_AABB;
    PointTypeXYZRGB min_point_OBB;
    PointTypeXYZRGB max_point_OBB;
    PointTypeXYZRGB position_OBB;
    Eigen::Matrix3f rotational_matrix_OBB;

private:
    PointCloudXYZRGB::Ptr loadpointcloud, pointcloud;
    PointCloudXYZRGB::Ptr pointcloud_inlierplane_manual;
    pcl::ModelCoefficients::Ptr coefficients;
    pcl::PointIndices::Ptr inliers;

};

#endif // POINTCLOUDTRANSFORM_H
