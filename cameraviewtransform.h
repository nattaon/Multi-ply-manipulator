#ifndef CAMERAVIEWTRANSFORM_H
#define CAMERAVIEWTRANSFORM_H

#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/surface/vtk_smoothing/vtk_utils.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/features/moment_of_inertia_estimation.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkCamera.h>


#include <QDebug>
#include <QTime>
#include <QObject>

typedef pcl::PointXYZ PointTypeXYZ;
typedef pcl::PointXYZRGB PointTypeXYZRGB;
typedef pcl::PointCloud<PointTypeXYZRGB> PointCloudXYZRGB;
typedef pcl::PointCloud<pcl::PointXYZ> PointCloudXYZ;

class CameraviewTransform : public QObject
{
        Q_OBJECT
public:
    CameraviewTransform();
    ~CameraviewTransform();

    void timerEvent(QTimerEvent *event);
    void mouse_callback_viewer_input( const pcl::visualization::MouseEvent& event, void* );


    void Resetview();
    void RotateViewUp();
    void RotateViewDown();
    void RotateViewLeft();
    void RotateViewRight();
    void ShowRawPointCloud(PointCloudXYZRGB::Ptr pc);
    void DrawPlane(pcl::ModelCoefficients::Ptr plane_coeff, std::string cloudname);
    void DrawPlane2(pcl::ModelCoefficients plane_coeff, std::string cloudname);

    void DrawTextAtPoint(PointTypeXYZ point_position, double text_scale,
        double r, double g, double b, std::string drawtext, std::string cloudname);
   // void DrawBoundingBox(PointTypeXYZRGB boxmin, PointTypeXYZRGB boxmax);
    void DrawBoundingBox(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);
    void RemoveBoundingBox();

private:

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_input;
    vtkSmartPointer<vtkCamera> camera;

    QTime time;
    int timerId;


};

#endif // CAMERAVIEWTRANSFORM_H
