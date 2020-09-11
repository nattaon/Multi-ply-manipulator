#ifndef POINTCLOUDTRANSFORM_H
#define POINTCLOUDTRANSFORM_H
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>

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
#include <pcl/filters/extract_indices.h>

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
    bool savePLY(QString filename);
    int GetRawPLYSize();
    PointCloudXYZRGB::Ptr GetRawPointCloud();
    void ApplyRotation(double rotate_angle, Eigen::Matrix<float, 1, 3>  rotation_axis);
    void ApplyPlaneSegmentation(double planeinlier_threshold);

private:
    PointCloudXYZRGB::Ptr pointcloud;
};

#endif // POINTCLOUDTRANSFORM_H
