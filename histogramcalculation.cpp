#include "histogramcalculation.h"


HistogramCalculation::HistogramCalculation()
{
    cv::namedWindow( "Histogram image", cv::WINDOW_AUTOSIZE );// Create a window for display.
    shownimage = cv::Mat(100, 100, CV_8UC3, cv::Scalar(0,0,0));
    black_img = cv::Mat(100, 100, CV_8UC3, cv::Scalar(0,0,0));
    histogram_log= "";
}
HistogramCalculation::~HistogramCalculation()
{
    cv::destroyWindow("Histogram image");
    shownimage.release();
    black_img.release();

}

bool HistogramCalculation::savePLY_cloud_norm(QString filename)
{
    if (filename.isEmpty ())
      return false;

    int return_status;

    if (filename.endsWith (".ply", Qt::CaseInsensitive))
      return_status = pcl::io::savePLYFileASCII (filename.toStdString(), *cloud_norm);
    else
    {
      filename.append(".ply");
      return_status = pcl::io::savePLYFileASCII (filename.toStdString(), *cloud_norm);
    }

    if (return_status != 0)
    {
      PCL_ERROR("Error writing point cloud %s\n", filename.toStdString().c_str());
      return false;
    }
    return true;
}
bool HistogramCalculation::savePLY_cloud_scale(QString filename)
{
    if (filename.isEmpty ())
      return false;

    int return_status;

    if (filename.endsWith (".ply", Qt::CaseInsensitive))
      return_status = pcl::io::savePLYFileASCII (filename.toStdString(), *cloud_scale);
    else
    {
      filename.append(".ply");
      return_status = pcl::io::savePLYFileASCII (filename.toStdString(), *cloud_scale);
    }

    if (return_status != 0)
    {
      PCL_ERROR("Error writing point cloud %s\n", filename.toStdString().c_str());
      return false;
    }
    return true;
}
void HistogramCalculation::SetColormap(int colorindex)
{

    switch(colorindex)
    {
        case 0 : cmaptype=Magma; break;
        case 1 : cmaptype=Inferno; break;
        case 2 : cmaptype=Plasma; break;
        case 3 : cmaptype=Viridis; break;
        case 4 : cmaptype=Cividis; break;
        case 5 : cmaptype=Parula; break;
        case 6 : cmaptype=JetMod; break;
    }
}
QString HistogramCalculation::GetColorname(int colorindex)
{

    switch(colorindex)
    {
        case 0 : return "Magma"; break;
        case 1 : return "Inferno"; break;
        case 2 : return "Plasma"; break;
        case 3 : return "Viridis"; break;
        case 4 : return "Cividis"; break;
        case 5 : return "Parula"; break;
        case 6 : return "JetMod"; break;
    }
}


float HistogramCalculation::GetColormap(int index, int rgb)
{
    switch(cmaptype)
    {
        case Magma  : return colormap.MagmaColormap[index][rgb];   break;
        case Inferno: return colormap.InfernoColormap[index][rgb]; break;
        case Plasma : return colormap.PlasmaColormap[index][rgb]; break;
        case Viridis: return colormap.ViridisColormap[index][rgb];   break;
        case Cividis: return colormap.CividisColormap[index][rgb]; break;
        case Parula : return colormap.ParulaColormap[index][rgb]; break;
        case JetMod : return colormap.JetModColormap[index][rgb]; break;
    }
}

void HistogramCalculation::SetHistogrameLogFile(QString filename)
{
    histogram_log_file.setFileName(filename);
    if ( histogram_log_file.open(QIODevice::ReadWrite) ) //create new if not exist
    {
        qDebug() << "opened  " << filename;
        QTextStream stream( &histogram_log_file );
        //int nn=11;
        //histogram_log.append("test22"+QString::number(nn));
        stream << histogram_log;
        histogram_log_file.close();
    }
    else
    {
        qDebug() << "cannot open " << filename;
    }
}

QString HistogramCalculation::PointXYZtoQString(pcl::PointXYZ pt)
{
    return QString::number(pt.x)+","+QString::number(pt.y)+","+QString::number(pt.z);
}

void HistogramCalculation::CalculateHistogram(PointCloudXYZRGB::Ptr pointcloud, int colormapindex)
{
    if(pointcloud->width == 0)
    {
        qDebug() << "no pointcloud load";
    }
    histogram_log= "";
    histogram_log.append("color "+GetColorname(colormapindex)+"\n");
    SetColormap(colormapindex);

    cloudxyz.reset(new PointCloudXYZ);
    cloud_norm.reset(new PointCloudXYZ);
    cloud_scale.reset(new PointCloudXYZ);

    std::cout << "points.size() " << pointcloud->points.size() << std::endl;
    histogram_log.append("points size "+QString::number(pointcloud->points.size())+"\n");

    pcl::copyPointCloud(*pointcloud, *cloudxyz);

    pcl::PointXYZ minpoint, maxpoint, boundingsize;
    pcl::getMinMax3D(*cloudxyz, minpoint, maxpoint);

    std::cout << "minpoint " << minpoint << std::endl;
    std::cout << "maxpoint " << maxpoint << std::endl;

    histogram_log.append("minpoint "+PointXYZtoQString(minpoint)+"\n");
    histogram_log.append("maxpoint "+PointXYZtoQString(maxpoint)+"\n");

    boundingsize.x = maxpoint.x - minpoint.x;
    boundingsize.y = maxpoint.y - minpoint.y;
    boundingsize.z = maxpoint.z - minpoint.z;

    std::cout << "boundingsize " << boundingsize << std::endl;
    histogram_log.append("bounding size "+PointXYZtoQString(boundingsize)+"\n");

    int img_width = (int)round(boundingsize.x *100);
    int img_height = (int)round(boundingsize.z *100);

    std::cout << "Image size " << img_width+1 << "*" << img_height+1 << std::endl;
    histogram_log.append("image w*h size "+QString::number(img_width+1)+" * "+QString::number(img_height+1)+"\n");

    //normalize 0-1
    pcl::copyPointCloud(*cloudxyz, *cloud_norm);
    for (size_t i = 0; i < cloud_norm->points.size(); ++i)
    {
      cloud_norm->points[i].x = (cloud_norm->points[i].x - minpoint.x )/ boundingsize.x;
      cloud_norm->points[i].y = (cloud_norm->points[i].y - minpoint.y )/ boundingsize.y;
      cloud_norm->points[i].z = (cloud_norm->points[i].z - minpoint.z )/ boundingsize.z;

    }

    pcl::copyPointCloud(*cloud_norm, *cloud_scale); // to keep int value of x and z as a pixel index
    for (size_t i = 0; i < cloud_scale->points.size (); ++i)
    {
      cloud_scale->points[i].x = round(cloud_scale->points[i].x * img_width);
      //cloud_scale->points[i].y = round(cloud_scale->points[i].y); //  * 255 hist_img using CV_8UC1 which range (0,255)
      cloud_scale->points[i].y =1; //for debug .ply easier
      cloud_scale->points[i].z = round(cloud_scale->points[i].z * img_height);

    }
    //cv::Mat histimg(rows,cols,type,value)
    cv::Mat histimg(img_height+1, img_width+1, CV_8UC1, cv::Scalar(0));
    cv::Mat histimg_color(img_height+1, img_width+1, CV_8UC3, cv::Scalar(0,0,0));

    std::cout << "histimg(0, 0) = " << (int)histimg.at<uchar>(0, 0)<< std::endl;

    std::cout <<  "[0] histimg.rows = " << histimg.rows << std::endl;//[0]
    std::cout <<  "[1] histimg.cols = " << histimg.cols << std::endl;//[1]


    //std::cout << "histimg("<<  img_width << "," << img_height << ") = " << (int)histimg.at<uchar>(img_width, img_height)<< std::endl;
    //std::cout << "histimg("<<  img_width+1 << "," << img_height+1 << ") = " << (int)histimg.at<uchar>(img_width+1, img_height+1)<< std::endl;


    int max_density=0;

    int hist_x, hist_y, hist_val;
    int histogram_arr[img_height+1][img_width+1]; // index 0,1,2,...,img_width
    //histogram_arr[0][0] will not be used? not true..

    //initialize histogram_arr
    for(int i= 0; i< img_height+1; i++)
      for(int j= 0; j< img_width+1; j++)
      {
        histogram_arr[i][j]=0;
      }

    // accumulate point that fall into a particular pixel
    for (size_t i = 0; i < cloud_scale->points.size() ; ++i) //
    {
      hist_x = (int)cloud_scale->points[i].x;
      hist_y = (int)cloud_scale->points[i].z;

      //if(hist_x < 0 || hist_y < 0 || hist_x > img_width || hist_y > img_height)
      //    std::cout <<hist_x <<"," << hist_y<<  std::endl;

      //hist_val = (int)cloud_scale->points[i].y; //don't care the value of the current pixel
      histimg.at<uchar>(hist_y, hist_x)++; // but count the number of points fall into the current pixel
      //histimg.at<uchar> would be max at 255 ...

      histogram_arr[hist_y][hist_x]++;

      // record max density
      if ( histogram_arr[hist_y][hist_x] > max_density)
      {
        max_density = histogram_arr[hist_y][hist_x];
        //std::cout <<hist_x <<"," << hist_y<< ": max_density=" << max_density << std::endl;
      }
    }
    std::cout << "max_density=" << (int)max_density << std::endl;
    histogram_log.append("max_density "+QString::number(max_density)+"\n");


    //int sum_density=cloud_scale->points.size(); // = all point?
    float total_pixel = histimg.rows*histimg.cols;
    float mean_density=cloud_scale->points.size()/total_pixel;
    float sum_variance=0;


    std::cout << "total_pixel=" << total_pixel << std::endl;
    histogram_log.append("total_pixel "+QString::number(total_pixel)+"\n");

    std::cout << "mean_density=" << mean_density << std::endl;
    histogram_log.append("mean_density "+QString::number(mean_density)+"\n");


    // find z score normalization
    for(int i= 0; i< img_height+1; i++)
        for(int j= 0; j< img_width+1; j++)
        {
            //variance += pow(val[i] - mean, 2);
            sum_variance+= pow(histogram_arr[i][j]-mean_density,2);
        }
    sum_variance=sum_variance/total_pixel;
    float stdDeviation = sqrt(sum_variance);

    std::cout << "stdDeviation=" << stdDeviation << std::endl;
    histogram_log.append("stdDeviation "+QString::number(stdDeviation)+"\n");

    histogram_log.append("i,j of histogram_arr density value, and its minmax, zscore normalized index\n");
    int c_index = 0;
    int z_index = 0;
    for(int i= 0; i< img_height+1; i++)
        for(int j= 0; j< img_width+1; j++)
        {
            //c_index=(int)histimg.at<uchar>(i, j);

            // min-max norm
            if(max_density>=255)
                c_index= histogram_arr[i][j];
            else
                c_index = (int)(255*histogram_arr[i][j]/max_density); //scale it up to 255

            //z-score norm
            z_index = (int)(255*(histogram_arr[i][j]-mean_density)/stdDeviation); //notwork...

            histogram_log.append(QString::number(i)+","+QString::number(j)+": "+QString::number(histogram_arr[i][j])+", "+QString::number(c_index)+", "+QString::number(z_index)+"\n");

            //std::cout<< i <<"," << j << " : c_index=" << c_index << std::endl;

            histimg_color.at<cv::Vec3b>(i, j)[0]= GetColormap(c_index,0)*255;
            histimg_color.at<cv::Vec3b>(i, j)[1]= GetColormap(c_index,1)*255;
            histimg_color.at<cv::Vec3b>(i, j)[2]= GetColormap(c_index,2)*255;
        }
    //cv::flip(histimg_color, histimg_color, 0); // flipy
    //cv::flip(histimg_color, histimg_color, 1); // flipx
    cv::flip(histimg_color, histimg_color, -1); // flipz?

    cv::cvtColor(histimg_color, histimg_color, cv::COLOR_BGR2RGB);
    cv::imshow( "Histogram image", histimg_color );


    shownimage = histimg_color.clone();

    histimg_color.release();
    histimg.release();


}

void HistogramCalculation::SaveHistogramImage(std::string filename)
{
    cv::imwrite( filename, shownimage );

    //cv::imshow( "Histogram image", black_img );
    //cv::destroyWindow("Histogram image");

}
