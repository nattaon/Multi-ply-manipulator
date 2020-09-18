/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSelect_ply_folder;
    QAction *actionSelect_img_folder;
    QAction *actionSet_points_origin_whole_folder;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab_pointcloud;
    QPushButton *bt_openplyfolder;
    QLineEdit *line_plyfoldername;
    QTreeWidget *plyfiles_treeWidget;
    QPushButton *bt_calchistogram;
    QLineEdit *line_prefiximg;
    QPushButton *bt_savehistimg;
    QPushButton *bt_saveply;
    QLabel *label_in_pointsize;
    QLabel *label_pointsize;
    QLineEdit *line_voxelfilter;
    QPushButton *bt_voxelfilter;
    QLabel *label_voxelsize;
    QPushButton *bt_viewleft;
    QPushButton *bt_viewright;
    QLabel *label_camera;
    QPushButton *bt_viewdown;
    QPushButton *bt_viewup;
    QPushButton *bt_resetcam;
    QLineEdit *line_x_rot;
    QPushButton *bt_xrot;
    QLineEdit *line_y_rot;
    QLineEdit *line_z_rot;
    QPushButton *bt_yrot;
    QPushButton *bt_zrot;
    QLabel *label_press_o;
    QLabel *label_pointcloud;
    QPushButton *bt_planeseg_1;
    QPushButton *bt_planeremove;
    QLabel *label_planeseginlier;
    QLineEdit *line_planeseg_inlier;
    QLineEdit *line_planecoef_a;
    QLineEdit *line_planecoef_b;
    QLineEdit *line_planecoef_c;
    QLabel *label_planecoef_in;
    QLineEdit *line_planecoef_d;
    QPushButton *bt_drawplan;
    QPushButton *bt_planestimate;
    QLabel *label;
    QLineEdit *line_outlier_meank;
    QLabel *label_2;
    QLineEdit *line_outlier_stddist;
    QPushButton *bt_outlierremove;
    QPushButton *bt_setpointorigin;
    QPushButton *bt_planeseg_2;
    QComboBox *comboBox_colormap;
    QPushButton *bt_histgraph1;
    QPushButton *bt_histgraph2;
    QLineEdit *line_histnameimg;
    QLineEdit *line_postfiximg;
    QPushButton *bt_xrot_plus;
    QPushButton *bt_xrot_minus;
    QPushButton *bt_yrot_plus;
    QPushButton *bt_yrot_minus;
    QPushButton *bt_zrot_plus;
    QPushButton *bt_zrot_minus;
    QCheckBox *checkBox_autocalchist;
    QPushButton *bt_setcam_y_front;
    QWidget *tab_label;
    QPushButton *bt_test1;
    QPushButton *bt_test2;
    QPushButton *pushButton_3;
    QLineEdit *line_test1;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuPointcloud;
    QMenu *menuHistogramImg;
    QMenu *menuLabelImg;
    QMenu *menuShortcut;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(650, 550);
        actionSelect_ply_folder = new QAction(MainWindow);
        actionSelect_ply_folder->setObjectName(QStringLiteral("actionSelect_ply_folder"));
        actionSelect_img_folder = new QAction(MainWindow);
        actionSelect_img_folder->setObjectName(QStringLiteral("actionSelect_img_folder"));
        actionSet_points_origin_whole_folder = new QAction(MainWindow);
        actionSet_points_origin_whole_folder->setObjectName(QStringLiteral("actionSet_points_origin_whole_folder"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 531, 471));
        tab_pointcloud = new QWidget();
        tab_pointcloud->setObjectName(QStringLiteral("tab_pointcloud"));
        bt_openplyfolder = new QPushButton(tab_pointcloud);
        bt_openplyfolder->setObjectName(QStringLiteral("bt_openplyfolder"));
        bt_openplyfolder->setGeometry(QRect(10, 10, 121, 25));
        line_plyfoldername = new QLineEdit(tab_pointcloud);
        line_plyfoldername->setObjectName(QStringLiteral("line_plyfoldername"));
        line_plyfoldername->setGeometry(QRect(140, 10, 351, 25));
        plyfiles_treeWidget = new QTreeWidget(tab_pointcloud);
        plyfiles_treeWidget->setObjectName(QStringLiteral("plyfiles_treeWidget"));
        plyfiles_treeWidget->setGeometry(QRect(10, 40, 191, 391));
        plyfiles_treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        plyfiles_treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        plyfiles_treeWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        bt_calchistogram = new QPushButton(tab_pointcloud);
        bt_calchistogram->setObjectName(QStringLiteral("bt_calchistogram"));
        bt_calchistogram->setGeometry(QRect(310, 380, 121, 25));
        line_prefiximg = new QLineEdit(tab_pointcloud);
        line_prefiximg->setObjectName(QStringLiteral("line_prefiximg"));
        line_prefiximg->setGeometry(QRect(210, 410, 51, 25));
        bt_savehistimg = new QPushButton(tab_pointcloud);
        bt_savehistimg->setObjectName(QStringLiteral("bt_savehistimg"));
        bt_savehistimg->setGeometry(QRect(450, 410, 71, 25));
        bt_saveply = new QPushButton(tab_pointcloud);
        bt_saveply->setObjectName(QStringLiteral("bt_saveply"));
        bt_saveply->setGeometry(QRect(420, 40, 71, 25));
        label_in_pointsize = new QLabel(tab_pointcloud);
        label_in_pointsize->setObjectName(QStringLiteral("label_in_pointsize"));
        label_in_pointsize->setGeometry(QRect(290, 40, 91, 20));
        label_pointsize = new QLabel(tab_pointcloud);
        label_pointsize->setObjectName(QStringLiteral("label_pointsize"));
        label_pointsize->setGeometry(QRect(210, 40, 71, 20));
        line_voxelfilter = new QLineEdit(tab_pointcloud);
        line_voxelfilter->setObjectName(QStringLiteral("line_voxelfilter"));
        line_voxelfilter->setGeometry(QRect(290, 70, 41, 25));
        bt_voxelfilter = new QPushButton(tab_pointcloud);
        bt_voxelfilter->setObjectName(QStringLiteral("bt_voxelfilter"));
        bt_voxelfilter->setGeometry(QRect(340, 70, 131, 25));
        label_voxelsize = new QLabel(tab_pointcloud);
        label_voxelsize->setObjectName(QStringLiteral("label_voxelsize"));
        label_voxelsize->setGeometry(QRect(210, 75, 67, 16));
        bt_viewleft = new QPushButton(tab_pointcloud);
        bt_viewleft->setObjectName(QStringLiteral("bt_viewleft"));
        bt_viewleft->setGeometry(QRect(210, 210, 21, 25));
        bt_viewright = new QPushButton(tab_pointcloud);
        bt_viewright->setObjectName(QStringLiteral("bt_viewright"));
        bt_viewright->setGeometry(QRect(270, 210, 21, 25));
        label_camera = new QLabel(tab_pointcloud);
        label_camera->setObjectName(QStringLiteral("label_camera"));
        label_camera->setGeometry(QRect(210, 140, 101, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_camera->setFont(font);
        bt_viewdown = new QPushButton(tab_pointcloud);
        bt_viewdown->setObjectName(QStringLiteral("bt_viewdown"));
        bt_viewdown->setGeometry(QRect(240, 240, 21, 25));
        bt_viewup = new QPushButton(tab_pointcloud);
        bt_viewup->setObjectName(QStringLiteral("bt_viewup"));
        bt_viewup->setGeometry(QRect(240, 180, 21, 25));
        bt_resetcam = new QPushButton(tab_pointcloud);
        bt_resetcam->setObjectName(QStringLiteral("bt_resetcam"));
        bt_resetcam->setGeometry(QRect(240, 210, 21, 25));
        line_x_rot = new QLineEdit(tab_pointcloud);
        line_x_rot->setObjectName(QStringLiteral("line_x_rot"));
        line_x_rot->setGeometry(QRect(350, 180, 31, 25));
        bt_xrot = new QPushButton(tab_pointcloud);
        bt_xrot->setObjectName(QStringLiteral("bt_xrot"));
        bt_xrot->setGeometry(QRect(310, 180, 41, 25));
        line_y_rot = new QLineEdit(tab_pointcloud);
        line_y_rot->setObjectName(QStringLiteral("line_y_rot"));
        line_y_rot->setGeometry(QRect(350, 210, 31, 25));
        line_z_rot = new QLineEdit(tab_pointcloud);
        line_z_rot->setObjectName(QStringLiteral("line_z_rot"));
        line_z_rot->setGeometry(QRect(350, 240, 31, 25));
        bt_yrot = new QPushButton(tab_pointcloud);
        bt_yrot->setObjectName(QStringLiteral("bt_yrot"));
        bt_yrot->setGeometry(QRect(310, 210, 41, 25));
        bt_zrot = new QPushButton(tab_pointcloud);
        bt_zrot->setObjectName(QStringLiteral("bt_zrot"));
        bt_zrot->setGeometry(QRect(310, 240, 41, 25));
        label_press_o = new QLabel(tab_pointcloud);
        label_press_o->setObjectName(QStringLiteral("label_press_o"));
        label_press_o->setGeometry(QRect(200, 125, 211, 20));
        label_pointcloud = new QLabel(tab_pointcloud);
        label_pointcloud->setObjectName(QStringLiteral("label_pointcloud"));
        label_pointcloud->setGeometry(QRect(420, 160, 101, 20));
        label_pointcloud->setFont(font);
        bt_planeseg_1 = new QPushButton(tab_pointcloud);
        bt_planeseg_1->setObjectName(QStringLiteral("bt_planeseg_1"));
        bt_planeseg_1->setGeometry(QRect(360, 280, 81, 25));
        bt_planeremove = new QPushButton(tab_pointcloud);
        bt_planeremove->setObjectName(QStringLiteral("bt_planeremove"));
        bt_planeremove->setGeometry(QRect(400, 310, 111, 25));
        label_planeseginlier = new QLabel(tab_pointcloud);
        label_planeseginlier->setObjectName(QStringLiteral("label_planeseginlier"));
        label_planeseginlier->setGeometry(QRect(210, 285, 101, 17));
        line_planeseg_inlier = new QLineEdit(tab_pointcloud);
        line_planeseg_inlier->setObjectName(QStringLiteral("line_planeseg_inlier"));
        line_planeseg_inlier->setGeometry(QRect(310, 280, 41, 25));
        line_planecoef_a = new QLineEdit(tab_pointcloud);
        line_planecoef_a->setObjectName(QStringLiteral("line_planecoef_a"));
        line_planecoef_a->setGeometry(QRect(280, 310, 25, 25));
        line_planecoef_b = new QLineEdit(tab_pointcloud);
        line_planecoef_b->setObjectName(QStringLiteral("line_planecoef_b"));
        line_planecoef_b->setGeometry(QRect(310, 310, 25, 25));
        line_planecoef_c = new QLineEdit(tab_pointcloud);
        line_planecoef_c->setObjectName(QStringLiteral("line_planecoef_c"));
        line_planecoef_c->setGeometry(QRect(340, 310, 25, 25));
        label_planecoef_in = new QLabel(tab_pointcloud);
        label_planecoef_in->setObjectName(QStringLiteral("label_planecoef_in"));
        label_planecoef_in->setGeometry(QRect(210, 315, 67, 17));
        line_planecoef_d = new QLineEdit(tab_pointcloud);
        line_planecoef_d->setObjectName(QStringLiteral("line_planecoef_d"));
        line_planecoef_d->setGeometry(QRect(370, 310, 25, 25));
        bt_drawplan = new QPushButton(tab_pointcloud);
        bt_drawplan->setObjectName(QStringLiteral("bt_drawplan"));
        bt_drawplan->setGeometry(QRect(210, 340, 89, 25));
        bt_planestimate = new QPushButton(tab_pointcloud);
        bt_planestimate->setObjectName(QStringLiteral("bt_planestimate"));
        bt_planestimate->setGeometry(QRect(310, 340, 121, 25));
        label = new QLabel(tab_pointcloud);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(210, 105, 51, 17));
        line_outlier_meank = new QLineEdit(tab_pointcloud);
        line_outlier_meank->setObjectName(QStringLiteral("line_outlier_meank"));
        line_outlier_meank->setGeometry(QRect(260, 100, 31, 25));
        label_2 = new QLabel(tab_pointcloud);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(300, 105, 51, 17));
        line_outlier_stddist = new QLineEdit(tab_pointcloud);
        line_outlier_stddist->setObjectName(QStringLiteral("line_outlier_stddist"));
        line_outlier_stddist->setGeometry(QRect(360, 100, 21, 25));
        bt_outlierremove = new QPushButton(tab_pointcloud);
        bt_outlierremove->setObjectName(QStringLiteral("bt_outlierremove"));
        bt_outlierremove->setGeometry(QRect(410, 100, 111, 25));
        bt_setpointorigin = new QPushButton(tab_pointcloud);
        bt_setpointorigin->setObjectName(QStringLiteral("bt_setpointorigin"));
        bt_setpointorigin->setGeometry(QRect(410, 130, 111, 25));
        bt_planeseg_2 = new QPushButton(tab_pointcloud);
        bt_planeseg_2->setObjectName(QStringLiteral("bt_planeseg_2"));
        bt_planeseg_2->setGeometry(QRect(440, 280, 81, 25));
        comboBox_colormap = new QComboBox(tab_pointcloud);
        comboBox_colormap->setObjectName(QStringLiteral("comboBox_colormap"));
        comboBox_colormap->setGeometry(QRect(210, 380, 91, 25));
        bt_histgraph1 = new QPushButton(tab_pointcloud);
        bt_histgraph1->setObjectName(QStringLiteral("bt_histgraph1"));
        bt_histgraph1->setGeometry(QRect(440, 350, 81, 25));
        bt_histgraph2 = new QPushButton(tab_pointcloud);
        bt_histgraph2->setObjectName(QStringLiteral("bt_histgraph2"));
        bt_histgraph2->setGeometry(QRect(440, 380, 81, 25));
        line_histnameimg = new QLineEdit(tab_pointcloud);
        line_histnameimg->setObjectName(QStringLiteral("line_histnameimg"));
        line_histnameimg->setGeometry(QRect(270, 410, 113, 25));
        line_postfiximg = new QLineEdit(tab_pointcloud);
        line_postfiximg->setObjectName(QStringLiteral("line_postfiximg"));
        line_postfiximg->setGeometry(QRect(390, 410, 51, 25));
        bt_xrot_plus = new QPushButton(tab_pointcloud);
        bt_xrot_plus->setObjectName(QStringLiteral("bt_xrot_plus"));
        bt_xrot_plus->setGeometry(QRect(450, 190, 31, 25));
        bt_xrot_minus = new QPushButton(tab_pointcloud);
        bt_xrot_minus->setObjectName(QStringLiteral("bt_xrot_minus"));
        bt_xrot_minus->setGeometry(QRect(450, 230, 31, 25));
        bt_yrot_plus = new QPushButton(tab_pointcloud);
        bt_yrot_plus->setObjectName(QStringLiteral("bt_yrot_plus"));
        bt_yrot_plus->setGeometry(QRect(410, 180, 31, 25));
        bt_yrot_minus = new QPushButton(tab_pointcloud);
        bt_yrot_minus->setObjectName(QStringLiteral("bt_yrot_minus"));
        bt_yrot_minus->setGeometry(QRect(490, 180, 31, 25));
        bt_zrot_plus = new QPushButton(tab_pointcloud);
        bt_zrot_plus->setObjectName(QStringLiteral("bt_zrot_plus"));
        bt_zrot_plus->setGeometry(QRect(480, 210, 31, 25));
        bt_zrot_minus = new QPushButton(tab_pointcloud);
        bt_zrot_minus->setObjectName(QStringLiteral("bt_zrot_minus"));
        bt_zrot_minus->setGeometry(QRect(420, 210, 31, 25));
        checkBox_autocalchist = new QCheckBox(tab_pointcloud);
        checkBox_autocalchist->setObjectName(QStringLiteral("checkBox_autocalchist"));
        checkBox_autocalchist->setGeometry(QRect(400, 250, 121, 23));
        checkBox_autocalchist->setChecked(true);
        bt_setcam_y_front = new QPushButton(tab_pointcloud);
        bt_setcam_y_front->setObjectName(QStringLiteral("bt_setcam_y_front"));
        bt_setcam_y_front->setGeometry(QRect(210, 160, 89, 20));
        tabWidget->addTab(tab_pointcloud, QString());
        tab_label = new QWidget();
        tab_label->setObjectName(QStringLiteral("tab_label"));
        tabWidget->addTab(tab_label, QString());
        bt_test1 = new QPushButton(centralWidget);
        bt_test1->setObjectName(QStringLiteral("bt_test1"));
        bt_test1->setGeometry(QRect(550, 80, 89, 25));
        bt_test2 = new QPushButton(centralWidget);
        bt_test2->setObjectName(QStringLiteral("bt_test2"));
        bt_test2->setGeometry(QRect(550, 110, 89, 25));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(550, 140, 89, 25));
        line_test1 = new QLineEdit(centralWidget);
        line_test1->setObjectName(QStringLiteral("line_test1"));
        line_test1->setGeometry(QRect(550, 50, 91, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 650, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuPointcloud = new QMenu(menuBar);
        menuPointcloud->setObjectName(QStringLiteral("menuPointcloud"));
        menuHistogramImg = new QMenu(menuBar);
        menuHistogramImg->setObjectName(QStringLiteral("menuHistogramImg"));
        menuLabelImg = new QMenu(menuBar);
        menuLabelImg->setObjectName(QStringLiteral("menuLabelImg"));
        menuShortcut = new QMenu(menuBar);
        menuShortcut->setObjectName(QStringLiteral("menuShortcut"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuPointcloud->menuAction());
        menuBar->addAction(menuHistogramImg->menuAction());
        menuBar->addAction(menuLabelImg->menuAction());
        menuBar->addAction(menuShortcut->menuAction());
        menuFile->addAction(actionSelect_ply_folder);
        menuFile->addSeparator();
        menuFile->addAction(actionSelect_img_folder);
        menuPointcloud->addAction(actionSet_points_origin_whole_folder);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionSelect_ply_folder->setText(QApplication::translate("MainWindow", "Select ply folder", Q_NULLPTR));
        actionSelect_img_folder->setText(QApplication::translate("MainWindow", "Select img folder", Q_NULLPTR));
        actionSet_points_origin_whole_folder->setText(QApplication::translate("MainWindow", "Set points origin whole folder", Q_NULLPTR));
        bt_openplyfolder->setText(QApplication::translate("MainWindow", "Open this folder", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = plyfiles_treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Filename", Q_NULLPTR));
        bt_calchistogram->setText(QApplication::translate("MainWindow", "Calc Histogram", Q_NULLPTR));
        line_prefiximg->setText(QString());
        bt_savehistimg->setText(QApplication::translate("MainWindow", "Save img", Q_NULLPTR));
        bt_saveply->setText(QApplication::translate("MainWindow", "Save PLY", Q_NULLPTR));
        label_in_pointsize->setText(QApplication::translate("MainWindow", "000000000", Q_NULLPTR));
        label_pointsize->setText(QApplication::translate("MainWindow", "Point size :", Q_NULLPTR));
        line_voxelfilter->setText(QApplication::translate("MainWindow", "0.01", Q_NULLPTR));
        bt_voxelfilter->setText(QApplication::translate("MainWindow", "Voxel filter points", Q_NULLPTR));
        label_voxelsize->setText(QApplication::translate("MainWindow", "Grid size", Q_NULLPTR));
        bt_viewleft->setText(QApplication::translate("MainWindow", "\342\206\220", Q_NULLPTR));
        bt_viewright->setText(QApplication::translate("MainWindow", "\342\206\222", Q_NULLPTR));
        label_camera->setText(QApplication::translate("MainWindow", "Camera View ", Q_NULLPTR));
        bt_viewdown->setText(QApplication::translate("MainWindow", "\342\206\223", Q_NULLPTR));
        bt_viewup->setText(QApplication::translate("MainWindow", "\342\206\221", Q_NULLPTR));
        bt_resetcam->setText(QApplication::translate("MainWindow", "Re", Q_NULLPTR));
        line_x_rot->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        bt_xrot->setText(QApplication::translate("MainWindow", "X-rot", Q_NULLPTR));
        line_y_rot->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        line_z_rot->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        bt_yrot->setText(QApplication::translate("MainWindow", "Y-rot", Q_NULLPTR));
        bt_zrot->setText(QApplication::translate("MainWindow", "Z-rot", Q_NULLPTR));
        label_press_o->setText(QApplication::translate("MainWindow", "(press 'o' to swap pers/ortho)", Q_NULLPTR));
        label_pointcloud->setText(QApplication::translate("MainWindow", "Pointcloud", Q_NULLPTR));
        bt_planeseg_1->setText(QApplication::translate("MainWindow", "PlaneSeg1", Q_NULLPTR));
        bt_planeremove->setText(QApplication::translate("MainWindow", "Plane removal", Q_NULLPTR));
        label_planeseginlier->setText(QApplication::translate("MainWindow", "inlier distance", Q_NULLPTR));
        line_planeseg_inlier->setText(QApplication::translate("MainWindow", "0.01", Q_NULLPTR));
        line_planecoef_a->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        line_planecoef_b->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        line_planecoef_c->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_planecoef_in->setText(QApplication::translate("MainWindow", "plan coef", Q_NULLPTR));
        line_planecoef_d->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        bt_drawplan->setText(QApplication::translate("MainWindow", "Draw Plan", Q_NULLPTR));
        bt_planestimate->setText(QApplication::translate("MainWindow", "Plane Estimation", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "meanK", Q_NULLPTR));
        line_outlier_meank->setText(QApplication::translate("MainWindow", "50", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "std dist", Q_NULLPTR));
        line_outlier_stddist->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        bt_outlierremove->setText(QApplication::translate("MainWindow", "Outlier remove", Q_NULLPTR));
        bt_setpointorigin->setText(QApplication::translate("MainWindow", "Set points origin", Q_NULLPTR));
        bt_planeseg_2->setText(QApplication::translate("MainWindow", "PlaneSeg2", Q_NULLPTR));
        comboBox_colormap->clear();
        comboBox_colormap->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Magma", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Inferno", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Plasma", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Viridis", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Cividis", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Parula", Q_NULLPTR)
         << QApplication::translate("MainWindow", "JetMod", Q_NULLPTR)
        );
        comboBox_colormap->setCurrentText(QApplication::translate("MainWindow", "Magma", Q_NULLPTR));
        bt_histgraph1->setText(QApplication::translate("MainWindow", "hist graph1", Q_NULLPTR));
        bt_histgraph2->setText(QApplication::translate("MainWindow", "hist graph2", Q_NULLPTR));
        line_postfiximg->setText(QApplication::translate("MainWindow", "-01", Q_NULLPTR));
        bt_xrot_plus->setText(QApplication::translate("MainWindow", "x +1", Q_NULLPTR));
        bt_xrot_minus->setText(QApplication::translate("MainWindow", "x -1", Q_NULLPTR));
        bt_yrot_plus->setText(QApplication::translate("MainWindow", "y +1", Q_NULLPTR));
        bt_yrot_minus->setText(QApplication::translate("MainWindow", "y -1", Q_NULLPTR));
        bt_zrot_plus->setText(QApplication::translate("MainWindow", "z +1", Q_NULLPTR));
        bt_zrot_minus->setText(QApplication::translate("MainWindow", "z -1", Q_NULLPTR));
        checkBox_autocalchist->setText(QApplication::translate("MainWindow", "Auto Calc Hist", Q_NULLPTR));
        bt_setcam_y_front->setText(QApplication::translate("MainWindow", "Y dir=front", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_pointcloud), QApplication::translate("MainWindow", "Pointcloud", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_label), QApplication::translate("MainWindow", "Labelling", Q_NULLPTR));
        bt_test1->setText(QApplication::translate("MainWindow", "Test 1", Q_NULLPTR));
        bt_test2->setText(QApplication::translate("MainWindow", "Test 2", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Test 3", Q_NULLPTR));
        line_test1->setText(QApplication::translate("MainWindow", "0.01", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuPointcloud->setTitle(QApplication::translate("MainWindow", "Pointcloud", Q_NULLPTR));
        menuHistogramImg->setTitle(QApplication::translate("MainWindow", "HistogramImg", Q_NULLPTR));
        menuLabelImg->setTitle(QApplication::translate("MainWindow", "LabelImg", Q_NULLPTR));
        menuShortcut->setTitle(QApplication::translate("MainWindow", "Shortcut", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
