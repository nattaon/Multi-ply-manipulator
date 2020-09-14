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
    viewer_input->removeAllShapes();
    viewer_input->removeAllPointClouds();
    viewer_input->addPointCloud(pc, "raw pointcloud");
    //viewer_input->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_SHADING, pcl::visualization::PCL_VISUALIZER_SHADING_PHONG, "raw pointcloud");
    //[setPointCloudRenderingProperties] Unknown property (7) specified!
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

void CameraviewTransform::DrawPlane(pcl::ModelCoefficients::Ptr plane_coeff, std::string cloudname)
{
/*
    pcl::ModelCoefficients plane_coeff;
    plane_coeff.values.resize (4);
    plane_coeff.values[0] = coefficients->values[0];
    plane_coeff.values[1] = coefficients->values[1];
    plane_coeff.values[2] = coefficients->values[2];
    plane_coeff.values[3] = coefficients->values[3];
*/

    viewer_input->removeShape(cloudname, 0);
    //addPlane (const pcl::ModelCoefficients &coefficients, const std::string &id="plane", int viewport=0)
    //viewer_input->addPlane(*plane_coeff, cloudname, 0);

    //addPlane (const pcl::ModelCoefficients &coefficients, double x, double y, double z, const std::string &id="plane", int viewport=0)
    viewer_input->addPlane(*plane_coeff, 0.0, 0.0, 0.0, cloudname, 0);

    viewer_input->spinOnce();
}
void CameraviewTransform::DrawPlane2(pcl::ModelCoefficients plane_coeff, std::string cloudname)
{


    viewer_input->removeShape(cloudname, 0);
    //addPlane (const pcl::ModelCoefficients &coefficients, const std::string &id="plane", int viewport=0)
    viewer_input->addPlane(plane_coeff, cloudname, 0);

    //addPlane (const pcl::ModelCoefficients &coefficients, double x, double y, double z, const std::string &id="plane", int viewport=0)
    //viewer_input->addPlane(plane_coeff, 0.0, 0.0, 0.0, cloudname, 0);


    viewer_input->spinOnce();
}

void CameraviewTransform::DrawTextAtPoint(PointTypeXYZ point_position, double text_scale,
    double r, double g, double b, std::string drawtext, std::string cloudname)
{
    viewer_input->removeText3D(cloudname);
    viewer_input->addText3D(drawtext, point_position, text_scale, r, g, b, cloudname);

    viewer_input->spinOnce();
}


