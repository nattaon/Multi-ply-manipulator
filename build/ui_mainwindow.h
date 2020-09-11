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
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab_pointcloud;
    QPushButton *bt_openplyfolder;
    QLineEdit *line_plyfoldername;
    QTreeWidget *plyfiles_treeWidget;
    QPushButton *bt_printinfo;
    QPushButton *bt_obb;
    QPushButton *bt_aabb;
    QPushButton *bt_calchistogram;
    QLabel *label_prefixhist;
    QLineEdit *line_prefiximg;
    QPushButton *bt_savehistimg;
    QPushButton *bt_saveply;
    QLabel *label_in_pointsize;
    QLabel *label_pointsize;
    QLineEdit *line_voxelfilter;
    QPushButton *bt_filter;
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
    QPushButton *bt_planeseg;
    QPushButton *bt_planeremove;
    QLabel *label_planeseginlier;
    QLineEdit *line_planeseg_inlier;
    QLineEdit *line_planecoef_a;
    QLineEdit *line_planecoef_b;
    QLineEdit *line_planecoef_c;
    QLabel *label_planecoef_in;
    QWidget *tab_label;
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
        MainWindow->resize(681, 527);
        actionSelect_ply_folder = new QAction(MainWindow);
        actionSelect_ply_folder->setObjectName(QStringLiteral("actionSelect_ply_folder"));
        actionSelect_img_folder = new QAction(MainWindow);
        actionSelect_img_folder->setObjectName(QStringLiteral("actionSelect_img_folder"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 531, 451));
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
        plyfiles_treeWidget->setGeometry(QRect(10, 40, 191, 371));
        plyfiles_treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        plyfiles_treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        plyfiles_treeWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        bt_printinfo = new QPushButton(tab_pointcloud);
        bt_printinfo->setObjectName(QStringLiteral("bt_printinfo"));
        bt_printinfo->setGeometry(QRect(400, 100, 89, 25));
        bt_obb = new QPushButton(tab_pointcloud);
        bt_obb->setObjectName(QStringLiteral("bt_obb"));
        bt_obb->setGeometry(QRect(210, 100, 70, 25));
        bt_aabb = new QPushButton(tab_pointcloud);
        bt_aabb->setObjectName(QStringLiteral("bt_aabb"));
        bt_aabb->setGeometry(QRect(300, 100, 70, 25));
        bt_calchistogram = new QPushButton(tab_pointcloud);
        bt_calchistogram->setObjectName(QStringLiteral("bt_calchistogram"));
        bt_calchistogram->setGeometry(QRect(210, 380, 121, 25));
        label_prefixhist = new QLabel(tab_pointcloud);
        label_prefixhist->setObjectName(QStringLiteral("label_prefixhist"));
        label_prefixhist->setGeometry(QRect(340, 382, 41, 20));
        line_prefiximg = new QLineEdit(tab_pointcloud);
        line_prefiximg->setObjectName(QStringLiteral("line_prefiximg"));
        line_prefiximg->setGeometry(QRect(390, 380, 51, 25));
        bt_savehistimg = new QPushButton(tab_pointcloud);
        bt_savehistimg->setObjectName(QStringLiteral("bt_savehistimg"));
        bt_savehistimg->setGeometry(QRect(440, 380, 71, 25));
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
        bt_filter = new QPushButton(tab_pointcloud);
        bt_filter->setObjectName(QStringLiteral("bt_filter"));
        bt_filter->setGeometry(QRect(340, 70, 89, 25));
        label_voxelsize = new QLabel(tab_pointcloud);
        label_voxelsize->setObjectName(QStringLiteral("label_voxelsize"));
        label_voxelsize->setGeometry(QRect(210, 75, 67, 17));
        bt_viewleft = new QPushButton(tab_pointcloud);
        bt_viewleft->setObjectName(QStringLiteral("bt_viewleft"));
        bt_viewleft->setGeometry(QRect(210, 210, 50, 25));
        bt_viewright = new QPushButton(tab_pointcloud);
        bt_viewright->setObjectName(QStringLiteral("bt_viewright"));
        bt_viewright->setGeometry(QRect(330, 210, 50, 25));
        label_camera = new QLabel(tab_pointcloud);
        label_camera->setObjectName(QStringLiteral("label_camera"));
        label_camera->setGeometry(QRect(210, 140, 101, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_camera->setFont(font);
        bt_viewdown = new QPushButton(tab_pointcloud);
        bt_viewdown->setObjectName(QStringLiteral("bt_viewdown"));
        bt_viewdown->setGeometry(QRect(270, 240, 50, 25));
        bt_viewup = new QPushButton(tab_pointcloud);
        bt_viewup->setObjectName(QStringLiteral("bt_viewup"));
        bt_viewup->setGeometry(QRect(270, 180, 50, 25));
        bt_resetcam = new QPushButton(tab_pointcloud);
        bt_resetcam->setObjectName(QStringLiteral("bt_resetcam"));
        bt_resetcam->setGeometry(QRect(270, 210, 50, 25));
        line_x_rot = new QLineEdit(tab_pointcloud);
        line_x_rot->setObjectName(QStringLiteral("line_x_rot"));
        line_x_rot->setGeometry(QRect(470, 180, 31, 25));
        bt_xrot = new QPushButton(tab_pointcloud);
        bt_xrot->setObjectName(QStringLiteral("bt_xrot"));
        bt_xrot->setGeometry(QRect(420, 180, 51, 25));
        line_y_rot = new QLineEdit(tab_pointcloud);
        line_y_rot->setObjectName(QStringLiteral("line_y_rot"));
        line_y_rot->setGeometry(QRect(470, 210, 31, 25));
        line_z_rot = new QLineEdit(tab_pointcloud);
        line_z_rot->setObjectName(QStringLiteral("line_z_rot"));
        line_z_rot->setGeometry(QRect(470, 240, 31, 25));
        bt_yrot = new QPushButton(tab_pointcloud);
        bt_yrot->setObjectName(QStringLiteral("bt_yrot"));
        bt_yrot->setGeometry(QRect(420, 210, 51, 25));
        bt_zrot = new QPushButton(tab_pointcloud);
        bt_zrot->setObjectName(QStringLiteral("bt_zrot"));
        bt_zrot->setGeometry(QRect(420, 240, 51, 25));
        label_press_o = new QLabel(tab_pointcloud);
        label_press_o->setObjectName(QStringLiteral("label_press_o"));
        label_press_o->setGeometry(QRect(210, 160, 211, 20));
        label_pointcloud = new QLabel(tab_pointcloud);
        label_pointcloud->setObjectName(QStringLiteral("label_pointcloud"));
        label_pointcloud->setGeometry(QRect(420, 150, 101, 20));
        label_pointcloud->setFont(font);
        bt_planeseg = new QPushButton(tab_pointcloud);
        bt_planeseg->setObjectName(QStringLiteral("bt_planeseg"));
        bt_planeseg->setGeometry(QRect(360, 280, 151, 25));
        bt_planeremove = new QPushButton(tab_pointcloud);
        bt_planeremove->setObjectName(QStringLiteral("bt_planeremove"));
        bt_planeremove->setGeometry(QRect(360, 310, 151, 25));
        label_planeseginlier = new QLabel(tab_pointcloud);
        label_planeseginlier->setObjectName(QStringLiteral("label_planeseginlier"));
        label_planeseginlier->setGeometry(QRect(210, 285, 101, 17));
        line_planeseg_inlier = new QLineEdit(tab_pointcloud);
        line_planeseg_inlier->setObjectName(QStringLiteral("line_planeseg_inlier"));
        line_planeseg_inlier->setGeometry(QRect(310, 280, 41, 25));
        line_planecoef_a = new QLineEdit(tab_pointcloud);
        line_planecoef_a->setObjectName(QStringLiteral("line_planecoef_a"));
        line_planecoef_a->setGeometry(QRect(280, 310, 20, 25));
        line_planecoef_b = new QLineEdit(tab_pointcloud);
        line_planecoef_b->setObjectName(QStringLiteral("line_planecoef_b"));
        line_planecoef_b->setGeometry(QRect(300, 310, 21, 25));
        line_planecoef_c = new QLineEdit(tab_pointcloud);
        line_planecoef_c->setObjectName(QStringLiteral("line_planecoef_c"));
        line_planecoef_c->setGeometry(QRect(320, 310, 21, 25));
        label_planecoef_in = new QLabel(tab_pointcloud);
        label_planecoef_in->setObjectName(QStringLiteral("label_planecoef_in"));
        label_planecoef_in->setGeometry(QRect(210, 315, 67, 17));
        tabWidget->addTab(tab_pointcloud, QString());
        tab_label = new QWidget();
        tab_label->setObjectName(QStringLiteral("tab_label"));
        tabWidget->addTab(tab_label, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 681, 22));
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

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionSelect_ply_folder->setText(QApplication::translate("MainWindow", "Select ply folder", Q_NULLPTR));
        actionSelect_img_folder->setText(QApplication::translate("MainWindow", "Select img folder", Q_NULLPTR));
        bt_openplyfolder->setText(QApplication::translate("MainWindow", "Open this folder", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = plyfiles_treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Filename", Q_NULLPTR));
        bt_printinfo->setText(QApplication::translate("MainWindow", "Print info", Q_NULLPTR));
        bt_obb->setText(QApplication::translate("MainWindow", "OBB", Q_NULLPTR));
        bt_aabb->setText(QApplication::translate("MainWindow", "AABB", Q_NULLPTR));
        bt_calchistogram->setText(QApplication::translate("MainWindow", "Calc Histogram", Q_NULLPTR));
        label_prefixhist->setText(QApplication::translate("MainWindow", "prefix", Q_NULLPTR));
        line_prefiximg->setText(QApplication::translate("MainWindow", "hist2_", Q_NULLPTR));
        bt_savehistimg->setText(QApplication::translate("MainWindow", "Save img", Q_NULLPTR));
        bt_saveply->setText(QApplication::translate("MainWindow", "Save PLY", Q_NULLPTR));
        label_in_pointsize->setText(QApplication::translate("MainWindow", "000000000", Q_NULLPTR));
        label_pointsize->setText(QApplication::translate("MainWindow", "Point size :", Q_NULLPTR));
        line_voxelfilter->setText(QApplication::translate("MainWindow", "0.01", Q_NULLPTR));
        bt_filter->setText(QApplication::translate("MainWindow", "Filter points", Q_NULLPTR));
        label_voxelsize->setText(QApplication::translate("MainWindow", "Voxel size", Q_NULLPTR));
        bt_viewleft->setText(QApplication::translate("MainWindow", "Left", Q_NULLPTR));
        bt_viewright->setText(QApplication::translate("MainWindow", "Right", Q_NULLPTR));
        label_camera->setText(QApplication::translate("MainWindow", "Camera View ", Q_NULLPTR));
        bt_viewdown->setText(QApplication::translate("MainWindow", "Down", Q_NULLPTR));
        bt_viewup->setText(QApplication::translate("MainWindow", "Up", Q_NULLPTR));
        bt_resetcam->setText(QApplication::translate("MainWindow", "Reset ", Q_NULLPTR));
        line_x_rot->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        bt_xrot->setText(QApplication::translate("MainWindow", "X-rot", Q_NULLPTR));
        line_y_rot->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        line_z_rot->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        bt_yrot->setText(QApplication::translate("MainWindow", "Y-rot", Q_NULLPTR));
        bt_zrot->setText(QApplication::translate("MainWindow", "Z-rot", Q_NULLPTR));
        label_press_o->setText(QApplication::translate("MainWindow", "(press 'o' to swap pers/ortho)", Q_NULLPTR));
        label_pointcloud->setText(QApplication::translate("MainWindow", "Pointcloud", Q_NULLPTR));
        bt_planeseg->setText(QApplication::translate("MainWindow", "Plane segmentation", Q_NULLPTR));
        bt_planeremove->setText(QApplication::translate("MainWindow", "Plane removal", Q_NULLPTR));
        label_planeseginlier->setText(QApplication::translate("MainWindow", "inlier distance", Q_NULLPTR));
        line_planeseg_inlier->setText(QApplication::translate("MainWindow", "0.01", Q_NULLPTR));
        line_planecoef_a->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        line_planecoef_b->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        line_planecoef_c->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_planecoef_in->setText(QApplication::translate("MainWindow", "plan coef", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_pointcloud), QApplication::translate("MainWindow", "Pointcloud", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_label), QApplication::translate("MainWindow", "Labelling", Q_NULLPTR));
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
