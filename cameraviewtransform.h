#ifndef CAMERAVIEWTRANSFORM_H
#define CAMERAVIEWTRANSFORM_H
#include <pcl/visualization/pcl_visualizer.h>


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
    void SetViewUp();
    void SetViewDown();
    void SetViewLeft();
    void SetViewRight();
    void ShowRawPointCloud(PointCloudXYZRGB::Ptr pc);

private:

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_input;
    vtkSmartPointer<vtkCamera> camera;

    QTime time;
    int timerId;


};

#endif // CAMERAVIEWTRANSFORM_H
