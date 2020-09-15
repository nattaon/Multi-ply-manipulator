#include "histogramcalculation.h"
#include "Colormap.cpp"

HistogramCalculation::HistogramCalculation()
{

}

void HistogramCalculation::CalculateHistogram(PointCloudXYZRGB::Ptr pointcloud, int colormapindex)
{
    if(pointcloud->width ==0)
    {
        qDebug() << "no pointcloud load";
    }
    Colormap color;

    cv::destroyWindow("Histogram image");

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudxyz (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_norm (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_scale (new pcl::PointCloud<pcl::PointXYZ>);

    pcl::copyPointCloud(*pointcloud, *cloudxyz);

    pcl::PointXYZ minpoint, maxpoint, boundingsize;
    pcl::getMinMax3D(*cloudxyz, minpoint, maxpoint);

    std::cout << "minpoint " << minpoint << std::endl;
    std::cout << "maxpoint " << maxpoint << std::endl;

    boundingsize.x = maxpoint.x - minpoint.x;
    boundingsize.y = maxpoint.y - minpoint.y;
    boundingsize.z = maxpoint.z - minpoint.z;

    std::cout << "boundingsize " << boundingsize << std::endl;

    int img_width = (int)round(boundingsize.x *100);
    int img_height = (int)round(boundingsize.z *100);

    std::cout << "Image size " << img_width << "*" << img_height << std::endl;

    //normalize 0-1
    pcl::copyPointCloud(*cloudxyz, *cloud_norm);
    for (size_t i = 0; i < cloud_norm->points.size (); ++i)
    {
      cloud_norm->points[i].x = (cloud_norm->points[i].x - minpoint.x )/ boundingsize.x;
      cloud_norm->points[i].y = (cloud_norm->points[i].y - minpoint.y )/ boundingsize.y;
      cloud_norm->points[i].z = (cloud_norm->points[i].z - minpoint.z )/ boundingsize.z;

    }

    pcl::copyPointCloud(*cloud_norm, *cloud_scale);
    for (size_t i = 0; i < cloud_scale->points.size (); ++i)
    {
      cloud_scale->points[i].x = round(cloud_scale->points[i].x * img_width);
      cloud_scale->points[i].y = round(cloud_scale->points[i].y * 255); // hist_img using CV_8UC1 which range (0,255)
      cloud_scale->points[i].z = round(cloud_scale->points[i].z * img_height);

    }

    cv::Mat histimg(img_width, img_height, CV_8UC1, cv::Scalar(0));
    cv::Mat histimg_color(img_width, img_height, CV_8UC3, cv::Scalar(0,0,0));

    std::cout << "histimg(0, 0) = " << (int)histimg.at<uchar>(0, 0)<< std::endl;
    std::cout << "histimg("<<  img_width << "," << img_height << ") = " << (int)histimg.at<uchar>(img_width, img_height)<< std::endl;
    std::cout << "histimg("<<  img_width+1 << "," << img_height+1 << ") = " << (int)histimg.at<uchar>(img_width+1, img_height+1)<< std::endl;

    std::cout <<  "histimg.rows = " << histimg.rows << std::endl;
    std::cout <<  "histimg.cols = " << histimg.cols << std::endl;

    int max_density=0;

    int hist_x, hist_y, hist_val;
    int histogram_arr[img_width+1][img_height+1]; // index 0,1,2,...,img_width
    //histogram_arr[0][0] will not be used? not true..

    //initialize histogram_arr
    for(int i= 0; i< img_width+1; i++)
      for(int j= 0; j< img_height+1; j++)
      {
        histogram_arr[i][j]=0;
      }

    for (size_t i = 0; i < cloud_scale->points.size () ; ++i) //
    {
      hist_x = (int)cloud_scale->points[i].x;
      hist_y = (int)cloud_scale->points[i].z;

      if(hist_x < 0 || hist_y < 0 || hist_x > img_width || hist_y > img_height)
          std::cout <<hist_x <<"," << hist_y<<  std::endl;

      hist_val = (int)cloud_scale->points[i].y; //don't care the value of the current pixel
      histimg.at<uchar>(hist_x, hist_y)++; // but count the number of points fall into the current pixel
      //histimg.at<uchar> would be max at 255 ...

      histogram_arr[hist_x][hist_y]++;

      if ( histogram_arr[hist_x][hist_y] > max_density)
      {
        max_density = histogram_arr[hist_x][hist_y];
        //std::cout <<hist_x <<"," << hist_y<< ": max_density=" << max_density << std::endl;
      }
    }
    std::cout << "max_density=" << (int)max_density << std::endl;


    //color.SetColormap("Magma");
    //color.cmaptype = Colormap::ColormapEnum::Magma;
    color.SetColormap(colormapindex);
    std::cout << "color[0]=" << color.GetColormap(0,0) << std::endl;

    int c_index = 0;


    for(int i= 0; i< histimg.rows; i++)
      for(int j= 0; j< histimg.cols; j++)
      {
        //c_index=(int)histimg.at<uchar>(i, j);
          c_index = (int)(255*histogram_arr[i][j]/max_density);

        //std::cout<< i <<"," << j << " : c_index=" << c_index << std::endl;
        //histimg_color.at<cv::Vec3b>(i, j)[0]= color.ViridisColormap[c_index][0]*255;
        //histimg_color.at<cv::Vec3b>(i, j)[1]= color.ViridisColormap[c_index][1]*255;
        //histimg_color.at<cv::Vec3b>(i, j)[2]= color.ViridisColormap[c_index][2]*255;
          histimg_color.at<cv::Vec3b>(i, j)[0]= color.GetColormap(c_index,0)*255;
          histimg_color.at<cv::Vec3b>(i, j)[1]= color.GetColormap(c_index,1)*255;
          histimg_color.at<cv::Vec3b>(i, j)[2]= color.GetColormap(c_index,2)*255;
      }
    cv::cvtColor(histimg_color, histimg_color, cv::COLOR_BGR2RGB);

    cv::namedWindow( "Histogram image", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::imshow( "Histogram image", histimg_color );

    shownimage = histimg_color.clone();


}

void HistogramCalculation::SaveHistogramImage(std::string filename)
{
    cv::imwrite( filename, shownimage );
    cv::destroyWindow("Histogram image");

}
