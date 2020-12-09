#include "pointcloudtransform.h"
#include <iostream>
PointcloudTransform::PointcloudTransform()
{
    //pointcloud initialize
    loadpointcloud.reset(new PointCloudXYZRGB);
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
    pcl::copyPointCloud(*pointcloud, *loadpointcloud);
    return true;
}
void PointcloudTransform::ReloadPLY()
{
    pcl::copyPointCloud(*loadpointcloud, *pointcloud); // copy A to B
}

bool PointcloudTransform::savePLY(QString filename)// save PointCloudXYZRGB::Ptr pointcloud
{
    if (filename.isEmpty ())
      return false;

    int return_status;

    if (filename.endsWith (".ply", Qt::CaseInsensitive))
      return_status = pcl::io::savePLYFileASCII (filename.toStdString(), *pointcloud);
    else
    {
      filename.append(".ply");
      return_status = pcl::io::savePLYFileASCII (filename.toStdString(), *pointcloud);
    }

    if (return_status != 0)
    {
      PCL_ERROR("Error writing point cloud %s\n", filename.toStdString().c_str());
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

    //pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    //pcl::PointIndices::Ptr inliers(new pcl::PointIndices);

    coefficients.reset(new pcl::ModelCoefficients);
    inliers.reset(new pcl::PointIndices);

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
void PointcloudTransform::ApplyPlaneSegmentationWithInlierPointcloud(double planeinlier_threshold)
{
    //pcl::SampleConsensusModelPlane<PointTypeXYZRGB>::Ptr dit (new pcl::SampleConsensusModelPlane<PointTypeXYZRGB> (pointcloud));
    //Eigen::VectorXf model_coefficients;
    //computeModelCoefficients (const Indices &samples, Eigen::VectorXf &model_coefficients)
    //[with Derived = Eigen::Matrix<float, -1, 1>; Eigen::DenseCoeffsBase<Derived, 1>::Scalar = float; Eigen::Index = long int]: Assertion `index >= 0 && index < size()' failed.
    //dit -> computeModelCoefficients(inliers, model_coefficients);
    //std::cout << "model_coefficients : "<< model_coefficients[0] << " " << model_coefficients[1] << " " << model_coefficients[2] <<  " " << model_coefficients[3] << std::endl;

    coefficients.reset(new pcl::ModelCoefficients);
    inliers.reset(new pcl::PointIndices);

    // 1. find pointclouds index(inlier) which is locate in plane
    pcl::SACSegmentation<PointTypeXYZRGB> seg;
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(planeinlier_threshold);
    seg.setInputCloud(pointcloud_inlierplane_manual);
    seg.segment(*inliers, *coefficients);

    //find coef by manual selected plane
    //coefficients : 4 : -0.00855 -0.997799 0.0657631 -3.58483
    std::cout << "coefficients : "<< coefficients->values.size()  << " : " << coefficients->values[0] << " " << coefficients->values[1] << " " << coefficients->values[2] <<  " " << coefficients->values[3] << std::endl;



    // do plane segmentation
    coefficients.reset(new pcl::ModelCoefficients);
    inliers.reset(new pcl::PointIndices);

    // 1. find pointclouds index(inlier) which is locate in plane
    //pcl::SACSegmentation<PointTypeXYZRGB> seg;
    //seg.setOptimizeCoefficients(true);
    //seg.setModelType(pcl::SACMODEL_PLANE);
    //seg.setMethodType(pcl::SAC_RANSAC);
    //seg.setDistanceThreshold(planeinlier_threshold);
    seg.setInputCloud(pointcloud);
    seg.segment(*inliers, *coefficients);

    // 2. extract plane and not plane pointcloud from inlier
    pcl::ExtractIndices<pcl::PointXYZRGB> extract;
    extract.setInputCloud(pointcloud);
    extract.setIndices(inliers);

    extract.setNegative(true);
    extract.filter(*pointcloud);


}
std::vector<int> PointcloudTransform::ApplyPlaneSegmentationWithParameter(double planeinlier_threshold, Eigen::Vector4f plane_coef)
{

    pcl::SampleConsensusModelPlane<PointTypeXYZRGB>::Ptr dit (new pcl::SampleConsensusModelPlane<PointTypeXYZRGB> (pointcloud));


    std::vector<int> inliers;
    //selectWithinDistance (const Eigen::VectorXf &model_coefficients, const double threshold, Indices &inliers)
    dit -> selectWithinDistance (plane_coef, planeinlier_threshold, inliers);

    std::cout << "selectWithinDistance : " << inliers.size();

    //Eigen::VectorXf model_coefficients;
    //computeModelCoefficients (const Indices &samples, Eigen::VectorXf &model_coefficients)

    //dit -> computeModelCoefficients(inliers, model_coefficients);
    //std::cout << "model_coefficients : "<< model_coefficients[0] << " " << model_coefficients[1] << " " << model_coefficients[2] <<  " " << model_coefficients[3] << std::endl;

    //dit -> selectWithinDistance (model_coefficients, 0.01, inliers);


    pointcloud_inlierplane_manual.reset(new PointCloudXYZRGB);
    pcl::copyPointCloud<PointTypeXYZRGB>(*pointcloud, inliers, *pointcloud_inlierplane_manual); // this will remain only the inlier area


    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    viewer->setBackgroundColor (0, 0, 0);
    viewer->setSize(500, 500);
    viewer->addPointCloud(pointcloud_inlierplane_manual, "pointcloud_inlierplane");
    viewer->addCoordinateSystem (1.0);
    viewer->initCameraParameters();

/* // doesn't help on programe terminate id close this window,
 * // the while loop also take control from mainui window, so we cant press any button...
    while (!viewer->wasStopped())
    {
      viewer->spinOnce (100);
      boost::this_thread::sleep (boost::posix_time::microseconds (100000));
    }
*/
    return inliers;




}

pcl::ModelCoefficients::Ptr PointcloudTransform::GetPlaneSegmentationParameter(double planeinlier_threshold)
{
    //PointCloudXYZRGB::Ptr before_applyplane_cloud;
    //pcl::copyPointCloud(*pointcloud, *before_applyplane_cloud);

    coefficients.reset(new pcl::ModelCoefficients);
    inliers.reset(new pcl::PointIndices);

    // 1. find pointclouds index(inlier) which is locate in plane
    pcl::SACSegmentation<PointTypeXYZRGB> seg;
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(planeinlier_threshold);
    seg.setInputCloud(pointcloud);
    //segment (PointIndices &inliers, ModelCoefficients &model_coefficients)
    seg.segment(*inliers, *coefficients);

    //coefficients : 4 : -0.00855 -0.997799 0.0657631 -3.58483
    //std::cout << "coefficients : "<< coefficients->values.size()  << " : " << coefficients->values[0] << " " << coefficients->values[1] << " " << coefficients->values[2] <<  " " << coefficients->values[3] << std::endl;
    return coefficients;

}


void PointcloudTransform::PlaneSegmentation1(double planeinlier_threshold)
{
    coefficients.reset(new pcl::ModelCoefficients);
    inliers.reset(new pcl::PointIndices);

    // 1. find pointclouds index(inlier) which is locate in plane
    pcl::SACSegmentation<PointTypeXYZRGB> seg;
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(planeinlier_threshold);
    seg.setInputCloud(pointcloud);
    //segment (PointIndices &inliers, ModelCoefficients &model_coefficients)
    seg.segment(*inliers, *coefficients);

    pointcloud_inlierplane_manual.reset(new PointCloudXYZRGB);
    //pcl::copyPointCloud<PointTypeXYZRGB>(*pointcloud, inliers, *pointcloud_inlierplane_manual); // this will remain only the inlier area
    pcl::ExtractIndices<pcl::PointXYZRGB> extract;
    extract.setInputCloud(pointcloud);
    extract.setIndices(inliers);

    extract.setNegative(false);
    extract.filter(*pointcloud_inlierplane_manual);

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    viewer->setBackgroundColor (0, 0, 0);
    viewer->setSize(500, 500);
    viewer->addPointCloud(pointcloud_inlierplane_manual, "pointcloud_inlierplane");
    viewer->addCoordinateSystem (1.0);
    viewer->initCameraParameters();
}

void PointcloudTransform::PlaneSegmentation2(double planeinlier_threshold)
{
    std::vector<int> inliers;

    pcl::SampleConsensusModelPlane<PointTypeXYZRGB>::Ptr model_p (new pcl::SampleConsensusModelPlane<PointTypeXYZRGB> (pointcloud));

    pcl::RandomSampleConsensus<PointTypeXYZRGB> ransac (model_p);
    ransac.setDistanceThreshold (planeinlier_threshold);
    ransac.computeModel();
    ransac.getInliers(inliers);

    pointcloud_inlierplane_manual.reset(new PointCloudXYZRGB);
    pcl::copyPointCloud<PointTypeXYZRGB>(*pointcloud, inliers, *pointcloud_inlierplane_manual); // this will remain only the inlier area


    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    viewer->setBackgroundColor (0, 0, 0);
    viewer->setSize(500, 500);
    viewer->addPointCloud(pointcloud_inlierplane_manual, "pointcloud_inlierplane");
    viewer->addCoordinateSystem (1.0);
    viewer->initCameraParameters();
}



void PointcloudTransform::FilterVoxelSize(double size)
{

    pcl::VoxelGrid<PointTypeXYZRGB> grid;

    //set scope for filter
    grid.setLeafSize(size, size, size);

    //set cloud to filter
    grid.setInputCloud(pointcloud);

    //do filter(save output in new pointcloud)
    PointCloudXYZRGB::Ptr cloud_filtered(new PointCloudXYZRGB);

    grid.filter(*cloud_filtered);


    //return pointcloud
    if (cloud_filtered->size() != 0)
    {
        pcl::copyPointCloud(*cloud_filtered, *pointcloud);
    }

    //show number of pointclound after apply filter
    //pcl::console::print_info( "after point clouds : %d\n", cloud->size() );
}

void PointcloudTransform::StatisticalOutlierRemoval(int meank, double stddev)
{


    //int meank = cloud->points.size()*meank_percentage*0.01;
    pcl::StatisticalOutlierRemoval<PointTypeXYZRGB> sor;
    sor.setInputCloud(pointcloud);
    sor.setMeanK(meank);//The number of neighbors to analyze for each point eg 50
    sor.setStddevMulThresh(stddev);//the standard deviation multiplier

    PointCloudXYZRGB::Ptr cloud_filtered(new PointCloudXYZRGB);

    sor.filter(*cloud_filtered);

    if (cloud_filtered->size() != 0)
    {
        pcl::copyPointCloud(*cloud_filtered, *pointcloud);
    }

}


void PointcloudTransform::PointcloudAlignAxis()
{
    pcl::VoxelGrid<PointTypeXYZRGB> grid;
    double size = 0.05;
    grid.setLeafSize(size, size, size);
    grid.setInputCloud(pointcloud);
    PointCloudXYZRGB::Ptr cloud_filtered(new PointCloudXYZRGB);
    grid.filter(*cloud_filtered);

    std::vector <float> moment_of_inertia;
    std::vector <float> eccentricity;
    float major_value, middle_value, minor_value;
    Eigen::Vector3f major_vector, middle_vector, minor_vector;


    pcl::MomentOfInertiaEstimation <PointTypeXYZRGB> feature_extractor;
    feature_extractor.setInputCloud(cloud_filtered);
    feature_extractor.compute();
    //feature_extractor.getMomentOfInertia (moment_of_inertia);
    //feature_extractor.getEccentricity (eccentricity);
    //feature_extractor.getAABB (min_point_AABB, max_point_AABB);
    //feature_extractor.getOBB(min_point_OBB, max_point_OBB, position_OBB, rotational_matrix_OBB);
    feature_extractor.getEigenValues (major_value, middle_value, minor_value);
    feature_extractor.getEigenVectors(major_vector, middle_vector, minor_vector);



    std::cout << "value " << major_value << "," << middle_value << "," << minor_value << std::endl;
    //std::cout << "major_vector " << major_vector << std::endl;
    //std::cout << "middle_vector " << middle_vector << std::endl;
    //std::cout << "minor_vector " << minor_vector << std::endl;
    //std::cout << "rotational_matrix_OBB " << rotational_matrix_OBB << std::endl;

    Eigen::Matrix<float, 1, 3> target_vector_x, target_vector_z;
    Eigen::Matrix<float, 1, 3> pointcloud_vector = Eigen::Matrix<float, 1, 3>(major_vector[0], major_vector[1], major_vector[2]);

    // 1. determine  x and z direction
    int Quater_id=0;
    if(major_vector[0] > 0 && major_vector[2] > 0)  // x+ z+
    {
        Quater_id=1;
        target_vector_x = Eigen::Matrix<float, 1, 3>(1.0, 0.0, 0.0);
        target_vector_z = Eigen::Matrix<float, 1, 3>(0.0, 0.0, 1.0);
    }
    else if(major_vector[0] > 0 && major_vector[2] < 0)  // x+ z-
    {
        Quater_id=2;
        target_vector_x = Eigen::Matrix<float, 1, 3>(1.0, 0.0, 0.0);
        target_vector_z = Eigen::Matrix<float, 1, 3>(0.0, 0.0, -1.0);
    }
    else if(major_vector[0] < 0 && major_vector[2] > 0)  // x- z+
    {
        Quater_id=3;
        target_vector_x = Eigen::Matrix<float, 1, 3>(-1.0, 0.0, 0.0);
        target_vector_z = Eigen::Matrix<float, 1, 3>(0.0, 0.0, 1.0);
    }
    else if(major_vector[0] < 0 && major_vector[2] < 0)  // x- z-
    {
        Quater_id=4;
        target_vector_x = Eigen::Matrix<float, 1, 3>(-1.0, 0.0, 0.0);
        target_vector_z = Eigen::Matrix<float, 1, 3>(0.0, 0.0, -1.0);
    }

    // 2. calculate direction to rotate (length=1)
    float theta_to_x = acos(pointcloud_vector.dot(target_vector_x));
    float theta_to_z = acos(pointcloud_vector.dot(target_vector_z));

    std::cout << "pointcloud_vector: " << pointcloud_vector << std::endl;
    std::cout << target_vector_x << " theta_to X: " << theta_to_x << " rad, " << theta_to_x*180/M_PI << " deg" << endl;
    std::cout << target_vector_z << " theta_to Z: " << theta_to_z << " rad, " << theta_to_z*180/M_PI << " deg" << endl;

    if(theta_to_x < theta_to_z)
    {
        if(Quater_id==1 || Quater_id==3) std::cout << "Suggest rotation on Y: +" ;
        else if(Quater_id==2 || Quater_id==4) std::cout << "Suggest rotation on Y: -" ;
        else std::cout << "Quater not in range!";

        std::cout << theta_to_x*180/M_PI << std::endl;
    }
    else if(theta_to_x > theta_to_z)
    {
        if(Quater_id==2 || Quater_id==4) std::cout << "Suggest rotation on Y: +" ;
        else if(Quater_id==1 || Quater_id==3) std::cout << "Suggest rotation on Y: -" ;
        else std::cout << "Quater not in range!";

        std::cout << theta_to_z*180/M_PI << std::endl;
    }
    else
    {
        std::cout << "ERROR theta_to_x = theta_to_z" << std::endl;
    }

    //std::cout << "min-max_point_OBB: " << min_point_OBB << max_point_OBB << std::endl;
    //std::cout << "min-max_point_AABB: " << min_point_AABB << max_point_AABB << std::endl;

    //Eigen::Matrix<float, 1, 3>  rotation_vector = pointcloud_vector.cross(target_vector);


    //float length_target_vector = sqrt(pow(target_vector[0], 2) + pow(target_vector[1], 2) + pow(target_vector[2], 2));
    //float length_pointcloud_vector =  sqrt(pow(pointcloud_vector[0], 2) + pow(pointcloud_vector[1], 2) + pow(pointcloud_vector[2], 2));

    //std::cout << "pointcloud_vector: " << pointcloud_vector << " ,length=" << length_pointcloud_vector << std::endl;
    //std::cout << "target_vector: " << target_vector << " ,length=" << length_target_vector << std::endl;


    //float theta = acos(pointcloud_vector.dot(target_vector) / (length_target_vector*length_pointcloud_vector));

    //Eigen::Affine3f transform = Eigen::Affine3f::Identity();
    //transform.rotate(Eigen::AngleAxisf(theta, rotation_vector));

    //cout << "Rotation Vector(perpendicular): " << rotation_vector << std::endl;
    //cout << "theta=" << theta << " rad, " << theta*180/M_PI << " deg" << endl;


    //transform.rotate(Eigen::AngleAxisf(rotate_angle*M_PI/180, rotation_axis));
    //ApplyRotation(theta,)
    //pcl::transformPointCloud(*pointcloud, *pointcloud, transform);
}

Eigen::Vector3f PointcloudTransform::CalculateMassCenter()
{

    pcl::MomentOfInertiaEstimation <PointTypeXYZRGB> feature_extractor;
    Eigen::Vector3f mass_center;

    feature_extractor.setInputCloud(pointcloud);
    feature_extractor.compute();
    feature_extractor.getMassCenter(mass_center);
    //feature_extractor.getEigenVectors(major_vector, middle_vector, minor_vector);
    //feature_extractor.getOBB(min_point_OBB, max_point_OBB, position_OBB, rotational_matrix_OBB);

    //mass_center_point.x = mass_center[0];
    //mass_center_point.y = mass_center[1];
    //mass_center_point.z = mass_center[2];

    return mass_center;

}
Eigen::Vector3f PointcloudTransform::CalculateMassCenterVoxel(double size)
{

    pcl::VoxelGrid<PointTypeXYZRGB> grid;
    grid.setLeafSize(size, size, size);
    grid.setInputCloud(pointcloud);
    PointCloudXYZRGB::Ptr cloud_filtered(new PointCloudXYZRGB);
    grid.filter(*cloud_filtered);

    //pcl::copyPointCloud(*cloud_filtered, *pointcloud);



    pcl::MomentOfInertiaEstimation <PointTypeXYZRGB> feature_extractor;
    Eigen::Vector3f mass_center;

    feature_extractor.setInputCloud(cloud_filtered);
    feature_extractor.compute();
    feature_extractor.getMassCenter(mass_center);


    //feature_extractor.getEigenVectors(major_vector, middle_vector, minor_vector);
    //feature_extractor.getOBB(min_point_OBB, max_point_OBB, position_OBB, rotational_matrix_OBB);

    //mass_center_point.x = mass_center[0];
    //mass_center_point.y = mass_center[1];
    //mass_center_point.z = mass_center[2];

    return mass_center;

}
void PointcloudTransform::MovePointCloudFromTo(PointTypeXYZRGB current_pos, PointTypeXYZRGB target_pos)
{

    double translate_x = target_pos.x - current_pos.x;
    double translate_y = target_pos.y - current_pos.y;
    double translate_z = target_pos.z - current_pos.z;

    Eigen::Affine3f transform = Eigen::Affine3f::Identity();
    transform.translation() << translate_x, translate_y, translate_z;

    pcl::transformPointCloud(*pointcloud, *pointcloud, transform);


}
void PointcloudTransform::GetBounding(PointTypeXYZRGB &minpoint, PointTypeXYZRGB &maxpoint)
{

    pcl::getMinMax3D(*pointcloud, minpoint, maxpoint);
    cout << "minpoint = " << minpoint << endl;
    cout << "maxpoint = " << maxpoint << endl;
}

void PointcloudTransform::PassthroughFilter( std::string axis, float min, float max)
{

    //cout << "filter " << axis << ":" << min << "," << max << endl;
    if (max == 99 || min == 99)
    {
        //cout << "nofilter" << endl;
        return;
    }
    PointCloudXYZRGB::Ptr cloud_filtered(new PointCloudXYZRGB);

    pcl::PassThrough<PointTypeXYZRGB> pass;

    pass.setInputCloud(pointcloud);
    pass.setFilterFieldName(axis);
    pass.setFilterLimits(min, max);
    //pass.setFilterLimitsNegative (true);
    pass.filter(*cloud_filtered);
    //pcl::console::print_info("cloud_filtered sized : %d\n", cloud_filtered->size());

    // cloud_filtered->size()==0 will cause error "vector subscript out of range"
    if (cloud_filtered->size() != 0)
    {
        pcl::copyPointCloud(*cloud_filtered, *pointcloud);
    }
    else
    {
        //cout << "cloud_filtered->size()==0 " << endl;

    }

}

void PointcloudTransform::SavePointCloudImage(std::string filename)
{
    //pcl::io::savePNGFile(filename, *pointcloud);  //  Image width exceeds user limit in IHDR libpng error: Invalid IHDR data

    pcl::io::savePNGFile(filename,*pointcloud,"intensity"); // need to be an organized pointcloud

   /*
    pcl::PCLImage image;

    //PointCloud<PointXYZRGB> cloud;
    //fromPCLPointCloud2 (*pointcloud, cloud);

    pcl::io::PointCloudImageExtractorFromRGBField<PointCloudXYZRGB> pcie;
    //pcie.setColorMode(pcie.COLORS_RGB_RANDOM);

    bool success = pcie.extract(pointcloud, image);
    std::cout << "success : " << success;

    if(success)
        pcl::io::saveImage (filename, image);

    */
}
