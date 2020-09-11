#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cameraviewtransform.h"
#include "histogramcalculation.h"
#include "pointcloudtransform.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QLocale>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

typedef pcl::PointXYZ PointTypeXYZ;
typedef pcl::PointXYZRGB PointTypeXYZRGB;
typedef pcl::PointCloud<PointTypeXYZRGB> PointCloudXYZRGB;
typedef pcl::PointCloud<pcl::PointXYZ> PointCloudXYZ;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CameraviewTransform *camview;
    PointcloudTransform *pctrans;
    HistogramCalculation * histcalc;

    QString currentPlyDir;
    int currentSelectingPlyIndex;


/*
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_input;
    PointCloudXYZRGB::Ptr pointcloud;
    QTime time;
    int timerId;
    double r,g,b;
    cv::Mat shownimage;



    int currentSelectingImageIndex;


    void timerEvent(QTimerEvent *event);
    void mouse_callback_viewer_input( const pcl::visualization::MouseEvent& event, void* );
    void loadPLY(QString filename, PointCloudXYZRGB::Ptr cloud);
    void PrintPoints(PointCloudXYZRGB::Ptr cloud);
*/
    void ListPlyInFolder();


private slots:

/*
    void Button_openfolder_clicked();
    void Button_printpoint_clicked();
    void Button_histogram_clicked();
    void Button_saveimg_clicked();

    void Button_obb_clicked();
    void Button_aabb_clicked();
    void SelectPlyFile(QTreeWidgetItem *item, int col);*/

    void on_bt_aabb_clicked();
    void on_bt_calchistogram_clicked();

    void on_bt_openplyfolder_clicked();
    void on_bt_saveply_clicked();
    void on_actionSelect_ply_folder_triggered();
    void on_plyfiles_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_plyfiles_treeWidget_itemSelectionChanged();
    void on_bt_resetcam_clicked();
    void on_bt_viewup_clicked();
    void on_bt_viewdown_clicked();
    void on_bt_viewleft_clicked();
    void on_bt_viewright_clicked();

    void on_bt_xrot_clicked();
    void on_bt_yrot_clicked();
    void on_bt_zrot_clicked();
    void on_bt_planeseg_clicked();
};

#endif // MAINWINDOW_H
