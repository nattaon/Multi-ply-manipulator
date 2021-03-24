#include "cameraviewtransform.h"

CameraviewTransform::CameraviewTransform()
{

    //pcl viewer
    viewer_input.reset(new pcl::visualization::PCLVisualizer("pointcloud input"));
    camera = viewer_input->getRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera();

    window_w =500;
    window_h = 500;
    Resetview();
    //viewer_input->setPosition(800,0);//window position

    viewer_input->addCoordinateSystem(3.0);
    //viewer_input->registerMouseCallback( &CameraviewTransform::mouse_callback_viewer_input, *this );

    timerId = startTimer(100); //call timerEvent every 100 msec
    time.start();

}

void CameraviewTransform::AddCoordinateSystem()
{
    viewer_input->addCoordinateSystem(3.0);
}
void CameraviewTransform::RemoveCoordinateSystem()
{
    viewer_input->removeCoordinateSystem();
}
void CameraviewTransform::SetWindowViewSize(int w, int h)
{
    window_w = w;
    window_h = h;
    viewer_input->setSize(window_w, window_h);
}

void CameraviewTransform::SetBGColorWhite()
{
    viewer_input->setBackgroundColor (1, 1, 1);
    isbgblack = false;
}
void CameraviewTransform::SetBGColorBlack()
{
    viewer_input->setBackgroundColor (0, 0, 0);
    isbgblack = true;
}
void CameraviewTransform::Resetview()
{
    viewer_input->initCameraParameters();

    if(isbgblack) SetBGColorBlack();
    else SetBGColorWhite();

    viewer_input->setSize(window_w, window_h);
    viewer_input->setPosition(800,0);//window position

    //camera->SetParallelProjection(1);
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

void CameraviewTransform::RotateViewUp()
{
    camera->Elevation(90.0); //rotate camera
}
void CameraviewTransform::RotateViewDown()
{
    camera->Elevation(-90.0);
}
void CameraviewTransform::RotateViewLeft()
{
    camera->Azimuth(-90.0);
}
void CameraviewTransform::RotateViewRight()
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

//void CameraviewTransform::DrawBoundingBox(PointTypeXYZRGB boxmin, PointTypeXYZRGB boxmax)
void CameraviewTransform::DrawBoundingBox(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max)
{/*
       Eigen::Vector3f position(position_OBB.x, position_OBB.y, position_OBB.z);
       Eigen::Quaternionf quat(rotational_matrix_OBB);

       cout << "ButtonBoundingBoxPressed "<< position << endl;

       double bb_xsize = max_point_OBB.x - min_point_OBB.x;
       double bb_ysize = max_point_OBB.y - min_point_OBB.y;
       double bb_zsize = max_point_OBB.z - min_point_OBB.z;
       ui->label_bb_xsize->setText(QString::number(bb_xsize));
       ui->label_bb_ysize->setText(QString::number(bb_ysize));
       ui->label_bb_zsize->setText(QString::number(bb_zsize));

       getActiveViewer(viewer_selecting)->removeShape("bounding box");
       getActiveViewer(viewer_selecting)->addCube(position, quat,
           max_point_OBB.x - min_point_OBB.x,
           max_point_OBB.y - min_point_OBB.y,
           max_point_OBB.z - min_point_OBB.z, "bounding box");
       //getActiveViewer(viewer_selecting)->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 1.0, 1.0, 0.0, "bounding box"); //cannotset on polygonmesh
       getActiveViewer(viewer_selecting)->setRepresentationToWireframeForAllActors(); // apply wireframe for all geometry
       //Viewer.setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_REPRESENTATION, pcl::visualization::PCL_VISUALIZER_REPRESENTATION_WIREFRAME, "AABB");

       getActiveViewer(viewer_selecting)->spinOnce();
   */
       viewer_input->removeShape("BoundingBox");
       //viewer_input->addCube(boxmin.x, boxmax.x, boxmin.y, boxmax.y, boxmin.z, boxmax.z, 1.0, 0.0, 0.0, "BoundingBox", 0);
       viewer_input->addCube(x_min, x_max, y_min, y_max, z_min, z_max, 1.0, 0.0, 0.0, "BoundingBox", 0);
       viewer_input->setRepresentationToWireframeForAllActors();
       //addCube (float x_min, float x_max, float y_min, float y_max, float z_min, float z_max, double r=1.0, double g=1.0, double b=1.0, const std::string &id="cube", int viewport=0)
       viewer_input->spinOnce();

}

void CameraviewTransform::DrawOBB(PointTypeXYZRGB position_OBB, PointTypeXYZRGB min_point_OBB, PointTypeXYZRGB max_point_OBB, Eigen::Matrix3f rotational_matrix_OBB)
{
    Eigen::Vector3f position(position_OBB.x, position_OBB.y, position_OBB.z);
    Eigen::Quaternionf quat(rotational_matrix_OBB);

    auto euler = quat.toRotationMatrix().eulerAngles(0, 1, 2);
    std::cout << "Euler from quaternion in roll, pitch, yaw"<< std::endl << euler[0]*180/M_PI<< std::endl << euler[1]*180/M_PI<< std::endl<< euler[2]*180/M_PI<< std::endl;

    viewer_input->removeShape("OBB");
    viewer_input->addCube(position, quat, max_point_OBB.x - min_point_OBB.x, max_point_OBB.y - min_point_OBB.y, max_point_OBB.z - min_point_OBB.z, "OBB");
    viewer_input->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_REPRESENTATION, pcl::visualization::PCL_VISUALIZER_REPRESENTATION_WIREFRAME, "OBB");
    viewer_input->spinOnce();

}
void CameraviewTransform::DrawSphere(PointTypeXYZRGB position, float rad, std::string name)
{
    viewer_input->removeShape(name);
    viewer_input->addSphere (position, rad, 0.5, 0.5, 0.0, name);

}
void CameraviewTransform::DrawLine(PointTypeXYZ p1, PointTypeXYZ p2, std::string name)
{
    viewer_input->removeShape(name);
    viewer_input->addLine (p1, p2, 1, 0.1, 1, name);

}

void CameraviewTransform::RemoveBoundingBox()
{
    viewer_input->removeShape("BoundingBox");
    //viewer_input->spinOnce();

}

void CameraviewTransform::SaveViewerScreenShot(std::string filename)
{
    viewer_input->saveScreenshot(filename);

}


