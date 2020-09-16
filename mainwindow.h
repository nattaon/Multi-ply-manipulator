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
#include <QHeaderView>
#include <QMessageBox>

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

    std::vector<int> plane_inliner_int;

    cv::Mat shown_hist_image;

    Eigen::Matrix<float, 1, 3>  rotation_vector_x,rotation_vector_y,rotation_vector_z;


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

    void on_bt_drawplan_clicked();
    void on_bt_planestimate_clicked();

    void on_bt_outlierremove_clicked();
    void on_bt_setpointorigin_clicked();
    void on_bt_voxelfilter_clicked();
    void on_bt_test1_clicked();
    void on_bt_test2_clicked();
    void on_pushButton_3_clicked();
    void on_bt_planeseg_1_clicked();
    void on_bt_planeseg_2_clicked();
    void on_bt_savehistimg_clicked();
    void on_actionSet_points_origin_whole_folder_triggered();
    void on_bt_histgraph1_clicked();
    void on_bt_histgraph2_clicked();
    void on_bt_xrot_minus_clicked();
    void on_bt_xrot_plus_clicked();
    void on_bt_yrot_minus_clicked();
    void on_bt_yrot_plus_clicked();
    void on_bt_zrot_minus_clicked();
    void on_bt_zrot_plus_clicked();


};

#endif // MAINWINDOW_H
