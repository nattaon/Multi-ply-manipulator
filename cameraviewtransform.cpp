#include "cameraviewtransform.h"

CameraviewTransform::CameraviewTransform()
{

    //pcl viewer
    viewer_input.reset(new pcl::visualization::PCLVisualizer("pointcloud input"));
    camera = viewer_input->getRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera();

    Resetview();

    viewer_input->addCoordinateSystem(3.0);
    //viewer_input->registerMouseCallback( &CameraviewTransform::mouse_callback_viewer_input, *this );

    timerId = startTimer(100); //call timerEvent every 100 msec
    time.start();

}
void CameraviewTransform::Resetview()
{
    viewer_input->initCameraParameters();
    viewer_input->setBackgroundColor(0, 0, 0);
    viewer_input->setSize(500, 500);
    viewer_input->setPosition(800,0);//window position

    camera->SetParallelProjection(1);
    //0=perspective (wider view), 1=orthogonal with clippping (narrow view..)
}
CameraviewTransform::~CameraviewTransform()
{
    killTimer(timerId);
}

void CameraviewTransform::timerEvent(QTimerEvent *event)
{
    viewer_input->spinOnce(100);
}
void CameraviewTransform::mouse_callback_viewer_input( const pcl::visualization::MouseEvent& event, void* )
{
    if( event.getType() == pcl::visualization::MouseEvent::MouseButtonPress && event.getButton() == pcl::visualization::MouseEvent::LeftButton ){
        std::cout << "viewer 0 Mouse : " << event.getX() << ", " << event.getY() << std::endl;
        //viewer_selecting = 0;
    }
}

void CameraviewTransform::ShowRawPointCloud(PointCloudXYZRGB::Ptr pc)
{
    viewer_input->removeAllPointClouds();
    viewer_input->addPointCloud(pc, "raw pointcloud");
    viewer_input->spinOnce();
}

void CameraviewTransform::SetViewUp()
{
    camera->Elevation(90.0);
}
void CameraviewTransform::SetViewDown()
{
    camera->Elevation(-90.0);
}
void CameraviewTransform::SetViewLeft()
{
    camera->Azimuth(-90.0);
}
void CameraviewTransform::SetViewRight()
{
    camera->Azimuth(90.0);
}
