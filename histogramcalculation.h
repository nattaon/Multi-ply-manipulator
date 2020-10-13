#ifndef HISTOGRAMCALCULATION_H
#define HISTOGRAMCALCULATION_H
#include "Colormap.cpp"

#include <iostream>
#include <QDebug>
#include <QFile>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>

#include <pcl/common/common_headers.h>
#include <pcl/common/common.h>
#include <pcl/common/io.h>
#include <pcl/common/transforms.h>

#include <pcl/console/parse.h>
#include <pcl/correspondence.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/features/moment_of_inertia_estimation.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
typedef pcl::PointXYZ PointTypeXYZ;
typedef pcl::PointXYZRGB PointTypeXYZRGB;
typedef pcl::PointCloud<PointTypeXYZRGB> PointCloudXYZRGB;
typedef pcl::PointCloud<pcl::PointXYZ> PointCloudXYZ;

class HistogramCalculation
{
public:
    HistogramCalculation();
    ~HistogramCalculation();
    void CalculateHistogram(PointCloudXYZRGB::Ptr pointcloud, int colormapindex, int &imgwidth, int &imgheight, int &maxdensity);
    void SaveHistogramImage(std::string filename);

    bool savePLY_cloud_norm(QString filename);
    bool savePLY_cloud_scale(QString filename);

    void SetColormap(int colorindex);
    float GetColormap(int index, int rgb);
    QString GetColorname(int colorindex);


    QString PointXYZtoQString(pcl::PointXYZ pt);
    void SaveHistogrameLogTextFile(QString filename);

    enum ColormapEnum { Magma, Inferno, Plasma , Viridis, Cividis, Parula, JetMod, PlasmaMod, ViridisMod, CividisMod};


private:
    cv::Mat shownimage, black_img;
    ColormapEnum cmaptype;
    Colormap colormap;
    PointCloudXYZ::Ptr cloudxyz,cloud_norm,cloud_scale;
    QFile histogram_log_file;
    QString histogram_log;
    int histogram_arr[3000][3000];


};

#endif // HISTOGRAMCALCULATION_H
