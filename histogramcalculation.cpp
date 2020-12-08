#include "histogramcalculation.h"


HistogramCalculation::HistogramCalculation()
{
    cv::namedWindow( "Histogram image", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::moveWindow("Histogram image", 0,0);
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
    if (filename.isEmpty ())return false;

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
      PCL_ERROR("savePLY_cloud_norm: Error writing point cloud %s\n", filename.toStdString().c_str());
      return false;
    }
    return true;
}
bool HistogramCalculation::savePLY_cloud_scale(QString filename)
{
    if (filename.isEmpty ()) return false;

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
      PCL_ERROR("savePLY_cloud_scale: Error writing point cloud %s\n", filename.toStdString().c_str());
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
        case 7 : cmaptype=PlasmaMod; break;
        case 8 : cmaptype=ViridisMod; break;
        case 9 : cmaptype=CividisMod; break;
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
        case 7 : return "PlasmaMod"; break;
        case 8 : return "ViridisMod"; break;
        case 9 : return "CividisMod"; break;
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
        case PlasmaMod: return colormap.PlasmaModColormap[index][rgb]; break;
        case ViridisMod: return colormap.ViridisModColormap[index][rgb];   break;
        case CividisMod: return colormap.CividisModColormap[index][rgb]; break;
    }
}

void HistogramCalculation::SaveHistogrameLogTextFile(QString filename)
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
        qDebug() << "SaveHistogrameLogTextFile: cannot open " << filename;
    }
}

QString HistogramCalculation::PointXYZtoQString(pcl::PointXYZ pt)
{
    return QString::number(pt.x)+","+QString::number(pt.y)+","+QString::number(pt.z);
}

void HistogramCalculation::CalculateHistogram(PointCloudXYZRGB::Ptr pointcloud, int colormapindex, int &imgwidth, int &imgheight, int &maxdensity)
{
    if(pointcloud->width == 0)
    {
        qDebug() << "no pointcloud load";
    }
    histogram_log= "";
    histogram_log.append("colormap "+GetColorname(colormapindex)+"\n");
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

    // if ratio width:height >10 ignore this data
/*    if(img_width > img_height)
        if (img_width > img_height*10)
        {
            printf("Ratio is more than 10, ignore this data ");
            return;
        }
    else if(img_width < img_height)
        if (img_width*10 < img_height)
        {
            printf("Ratio is more than 10, ignore this data ");
            return;
        }
*/
    imgwidth = img_width+1; //pass by reference for return img size value
    imgheight = img_height+1;
    std::cout << "Image size " << img_width+1 << "*" << img_height+1 << std::endl;
    histogram_log.append("image w*h size "+QString::number(img_width+1)+" * "+QString::number(img_height+1)+"\n");


    // # 1. Normalize pointcloud to [0,1]
    qDebug() << "# 1. Normalize pointcloud to [0,1]";
    pcl::copyPointCloud(*cloudxyz, *cloud_norm);
    for (size_t i = 0; i < cloud_norm->points.size(); ++i)
    {
      cloud_norm->points[i].x = (cloud_norm->points[i].x - minpoint.x )/ boundingsize.x;
      cloud_norm->points[i].y = (cloud_norm->points[i].y - minpoint.y )/ boundingsize.y;
      cloud_norm->points[i].z = (cloud_norm->points[i].z - minpoint.z )/ boundingsize.z;
    }

    // # 2. Scale pointcloud x and z to [0,img size]
    qDebug() << "# 2. Scale pointcloud x and z to [0,img size]";
    pcl::copyPointCloud(*cloud_norm, *cloud_scale); // to keep int value of x and z as a pixel index
    for (size_t i = 0; i < cloud_scale->points.size (); ++i)
    {
      cloud_scale->points[i].x = round(cloud_scale->points[i].x * img_width);
      cloud_scale->points[i].y =1; //for easier debug cloud_scale.ply
      cloud_scale->points[i].z = round(cloud_scale->points[i].z * img_height);
    }

    // # 3. Create histogram_arr[][] to count density of each pixel

    //qDebug() << "# 3-initialize. Create histogram_arr[][] to count density of each pixel";
    //int histogram_arr[img_height+1][img_width+1]; // index 0,1,2,...,img_width

    //int *histogram_arr = new int[imgwidth*imgheight];

  /*   int** histogram_arr = new int*[img_height+1];
     for(int i = 0; i < img_height+1; ++i)
      histogram_arr[i] = new int[img_width+1];
        for(int j= 0; j< img_width+1; j++)
        {
          histogram_arr[i][j]=0; // initialize histogram_arr
        }*/

    qDebug() << "# 3-int histogram_arr";
    for(int i= 0; i< img_height+1; i++)
      for(int j= 0; j< img_width+1; j++)
      {
        histogram_arr[i][j]=0; // initialize histogram_arr
      }

    qDebug() << "# 3-count. Create histogram_arr[][] to count density of each pixel";
    int pixel_x, pixel_y, max_density=0;
    for (size_t i = 0; i < cloud_scale->points.size() ; ++i)
    {
      //std::cout << i << std::endl;
      pixel_x = (int)cloud_scale->points[i].x;
      pixel_y = (int)cloud_scale->points[i].z;
      histogram_arr[pixel_y][pixel_x]++; // accumulate point that fall into a particular pixel
      //std::cout << histogram_arr[pixel_y][pixel_x] << std::endl;

      // save the max density
      if ( histogram_arr[pixel_y][pixel_x] > max_density)
      { //std::cout << i << ": max_density=" << histogram_arr[pixel_y][pixel_x] << std::endl;
        max_density = histogram_arr[pixel_y][pixel_x];
      }
    }
    std::cout << "max_density=" << (int)max_density << std::endl;
    histogram_log.append("max_density "+QString::number(max_density)+"\n");
    maxdensity=max_density;//pass by reference


    //int sum_density=cloud_scale->points.size(); // = all point?
    float total_pixel = (img_height+1) * (img_width+1);
    float mean_density=cloud_scale->points.size()/total_pixel;
    float sum_variance=0;


    std::cout << "total_pixel=" << total_pixel << std::endl;
    histogram_log.append("total_pixel "+QString::number(total_pixel)+"\n");

    std::cout << "mean_density=" << mean_density << std::endl;
    histogram_log.append("mean_density "+QString::number(mean_density)+"\n");



    // # 4. Create cv::Mat to convert histogram_arr[i][j] to color image //cv::Mat histimg(rows,cols,type,initvalue)
    cv::Mat histimg_color(img_height+1, img_width+1, CV_8UC3, cv::Scalar(0,0,0));
    //std::cout << "histimg(0, 0) = " << (int)histimg.at<uchar>(0, 0)<< std::endl;

    std::cout <<  "[0] histimg_color.rows = " << histimg_color.rows << std::endl;//[0]
    std::cout <<  "[1] histimg_color.cols = " << histimg_color.cols << std::endl;//[1]


    histogram_log.append("i,j of histogram_arr density value, its normalized index, rgb\n");
    int c_index,r,g,b;
    for(int i= 0; i< img_height+1; i++)
        for(int j= 0; j< img_width+1; j++)
        {
            // if maxdensity < 255, do [0,255]scale
            // if density > 255,  clamp to 255
            /*
            if(max_density<255)
                c_index = (int)(255*histogram_arr[i][j]/max_density); //scale it up to 255
            else if (histogram_arr[i][j]>=255)
                c_index = 255;// histogram_arr[i][j];
            else
                c_index = histogram_arr[i][j];
            */
            c_index = (int)(255*histogram_arr[i][j]/max_density); //scale it up to 255

            r= GetColormap(c_index,0)*255;
            g= GetColormap(c_index,1)*255;
            b= GetColormap(c_index,2)*255;
            histimg_color.at<cv::Vec3b>(i, j)[0]= r;
            histimg_color.at<cv::Vec3b>(i, j)[1]= g;
            histimg_color.at<cv::Vec3b>(i, j)[2]= b;

            histogram_log.append(QString::number(i)+","+QString::number(j)+": "+QString::number(histogram_arr[i][j])+", "+QString::number(c_index)+"; ");
            histogram_log.append(QString::number(r)+","+QString::number(g)+","+QString::number(b)+"\n");
        }


    cv::flip(histimg_color, histimg_color, -1); // flipz?
    cv::cvtColor(histimg_color, histimg_color, cv::COLOR_BGR2RGB);
    cv::imshow( "Histogram image", histimg_color );


    shownimage = histimg_color.clone();

    histimg_color.release();

    /*for(int i = 0; i < img_height+1; i++) {
        delete [] histogram_arr[i];
    }
    delete [] histogram_arr;*/


}

void HistogramCalculation::SaveHistogramImage(std::string filename)
{
    cv::imwrite( filename, shownimage );

    //cv::imshow( "Histogram image", black_img );
    //cv::destroyWindow("Histogram image");

}
