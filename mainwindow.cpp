#include "mainwindow.h"
#include "build/ui_mainwindow.h"

#include "JetColormap.cpp"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    camview = new CameraviewTransform();
    pctrans = new PointcloudTransform();
    histcalc = new HistogramCalculation();

    //Show list of ply files
    //currentlyOpenedDir ="/home/okuboali/nattaon_ws/_0room_dataset/nattaon_edited_sceneNN/rotated";
    currentPlyDir = QString("%1home%1nattaon%1ply%1OriginalPointCloud").arg(QDir::separator());
    ui->line_plyfoldername->setText(currentPlyDir);
    ListPlyInFolder();
    currentSelectingPlyIndex=-1;


}
MainWindow::~MainWindow()
{
    delete ui;
}

// // LOAD PLY ///

void MainWindow::on_actionSelect_ply_folder_triggered()
{
    currentPlyDir = QFileDialog::getExistingDirectory(this, "Choose a directory to be read .ply in");
    if (currentPlyDir.isEmpty())
        return;

    ui->line_plyfoldername->setText(currentPlyDir);
    ListPlyInFolder();
    currentSelectingPlyIndex=-1;
}

void MainWindow::on_bt_openplyfolder_clicked()
{
    ListPlyInFolder();
    currentSelectingPlyIndex=-1;
}
void MainWindow::ListPlyInFolder()
{
    currentPlyDir=ui->line_plyfoldername->text();
    qDebug() << " currentPlyDir =  " << currentPlyDir;

    QDir directory(currentPlyDir);
    QStringList nameFilters;
    nameFilters << "*.ply";
    //nameFilters << "*.ply" << "*.pcd";

    QStringList files = directory.entryList(nameFilters, QDir::Files);
    qDebug() << " total files in folder =  " << files.size();
    if (files.size() <= 0)
        return;

    ui->plyfiles_treeWidget->clear();
    for (int i = 0; i < files.size(); i++)
    {
        QTreeWidgetItem *currentFile = new QTreeWidgetItem(ui->plyfiles_treeWidget);
        currentFile->setText(0, files[i]);
    }

    //currentSelectingImageIndex=-1;
    //Button_nextimg_clicked();

}
void MainWindow::on_plyfiles_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(currentSelectingPlyIndex == ui->plyfiles_treeWidget->currentIndex().row()) //if a user click on a current file -> do nothing
    {
        return;
    }
    currentSelectingPlyIndex = ui->plyfiles_treeWidget->currentIndex().row(); //assign a current selecting index
    QString filename = currentPlyDir + QDir::separator() + item->text(0); //concat ply filename path
    qDebug() << filename;

    if(pctrans->loadPLY(filename)) // load pointcloud
    {
        camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
        int pointsize = pctrans->GetRawPLYSize();
        ui->label_in_pointsize->setText(QLocale(QLocale::English).toString(pointsize));//add comma to number

    }

}

// thinking about this function, would it should load PLY by keyboard selecting, the user may accidently press the key.
// however, itemSelectionChanged() deactivate treeWidget_itemClicked(QTreeWidgetItem *item, int column)
void MainWindow::on_plyfiles_treeWidget_itemSelectionChanged()
{
    int SelectingPlyIndex = ui->plyfiles_treeWidget->currentIndex().row(); //assign a current selecting index
    //QString filename = currentPlyDir + QDir::separator() + item->text(0); //concat ply filename path
    qDebug() << "Select ply index " << SelectingPlyIndex;

    QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(SelectingPlyIndex);
    on_plyfiles_treeWidget_itemClicked(item,0); // call treeWidget_itemClicked(QTreeWidgetItem *item, int column)

}

void MainWindow::on_bt_saveply_clicked()
{

    QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(currentSelectingPlyIndex);
    QString suggestionname = currentPlyDir + QDir::separator() + item->text(0); //concat ply filename path
    QString filename = QFileDialog::getSaveFileName(this, tr ("Save .ply"), suggestionname, tr ("Pointcloud file(*.ply)"));

    //PCL_INFO("File chosen: %s\n", filename.toStdString().c_str ());

    bool saveresult = pctrans->savePLY(filename);
}


// // CAMERA VIEW ///

void MainWindow::on_bt_resetcam_clicked()
{
    camview->Resetview();
}
void MainWindow::on_bt_viewup_clicked()
{
    camview->SetViewUp();
}

void MainWindow::on_bt_viewdown_clicked()
{
    camview->SetViewDown();
}

void MainWindow::on_bt_viewleft_clicked()
{
    camview->SetViewLeft();
}

void MainWindow::on_bt_viewright_clicked()
{
    camview->SetViewRight();
}

// // POINTCLOUD MANIPULATION ///

void MainWindow::on_bt_xrot_clicked()
{
    double rotate_x = ui->line_x_rot->text().toDouble();
    Eigen::Matrix<float, 1, 3>  rotation_vector_x(1.0, 0.0, 0.0);

    pctrans->ApplyRotation(rotate_x,rotation_vector_x);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
}

void MainWindow::on_bt_yrot_clicked()
{
    double rotate_y = ui->line_y_rot->text().toDouble();
    Eigen::Matrix<float, 1, 3>  rotation_vector_y(0.0, 1.0, 0.0);

    pctrans->ApplyRotation(rotate_y,rotation_vector_y);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
}

void MainWindow::on_bt_zrot_clicked()
{
    double rotate_z = ui->line_z_rot->text().toDouble();
    Eigen::Matrix<float, 1, 3>  rotation_vector_z(0.0, 0.0, 1.0);

    pctrans->ApplyRotation(rotate_z,rotation_vector_z);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
}
void MainWindow::on_bt_planeseg_clicked()
{
    double planeseg_threshold = ui->line_planeseg_inlier->text().toDouble();
    /*pcl::ModelCoefficients plane_coeff;
    plane_coeff.values.resize (4);
    plane_coeff.values[0] = ui->line_planecoef_a->text().toDouble();
    plane_coeff.values[1] = ui->line_planecoef_b->text().toDouble();
    plane_coeff.values[2] = ui->line_planecoef_c->text().toDouble();
    plane_coeff.values[3] = ui->line_planecoef_d->text().toDouble();*/



    pctrans->ApplyPlaneSegmentationWithInlierPointcloud(planeseg_threshold);




    //pctrans->ApplyPlaneSegmentation(planeseg_threshold);

    //Debug: drawing a plane equation
    //pcl::ModelCoefficients::Ptr plancoef = pctrans->GetPlaneSegmentationParameter(planeseg_threshold);
    //std::cout << "plancoef : "<< plancoef->values.size()  << " : " << plancoef->values[0] << " " << plancoef->values[1] << " " << plancoef->values[2] <<  " " << plancoef->values[3] << std::endl;
    //camview->DrawPlane(plancoef,"planseg");



    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    qDebug() << "remain points " << pctrans->GetRawPLYSize();
}


void MainWindow::on_bt_planestimate_clicked()
{
    double planeseg_threshold = ui->line_planeseg_inlier->text().toDouble();
    Eigen::Vector4f plane_coeff = Eigen::Vector4f(ui->line_planecoef_a->text().toDouble(), ui->line_planecoef_b->text().toDouble(),
                                                   ui->line_planecoef_c->text().toDouble(), ui->line_planecoef_d->text().toDouble());
    plane_inliner_int = pctrans->ApplyPlaneSegmentationWithParameter(planeseg_threshold, plane_coeff);

    //std::cout << "plane_inliner_int size : " << plane_inliner_int.size();  //print nothing dont know why..
    qDebug() << "plane_inliner_int size : " << plane_inliner_int.size();

}
void MainWindow::on_bt_planeseg_1_clicked()
{
    double threshold = ui->line_planeseg_inlier->text().toDouble();
    pctrans->PlaneSegmentation1(threshold);
}

void MainWindow::on_bt_planeseg_2_clicked()
{
    double threshold = ui->line_planeseg_inlier->text().toDouble();
    pctrans->PlaneSegmentation2(threshold);
}

void MainWindow::on_bt_drawplan_clicked()
{
    //double coef_a = ui->line_planecoef_a->text().toDouble();
    //double coef_b = ui->line_planecoef_b->text().toDouble();
    //double coef_c = ui->line_planecoef_c->text().toDouble();
    //double coef_d = ui->line_planecoef_d->text().toDouble();

    pcl::ModelCoefficients plane_coeff;
    plane_coeff.values.resize (4);
    plane_coeff.values[0] = ui->line_planecoef_a->text().toDouble();
    plane_coeff.values[1] = ui->line_planecoef_b->text().toDouble();
    plane_coeff.values[2] = ui->line_planecoef_c->text().toDouble();
    plane_coeff.values[3] = ui->line_planecoef_d->text().toDouble();

    camview->DrawPlane2(plane_coeff,"plane");

    pcl::PointXYZ point;
    point.x=0;
    point.y=0;
    point.z=0;
//  QString text_coef = ui->line_planecoef_a->text() + "," + ui->line_planecoef_b->text()+ "," + ui->line_planecoef_c->text()+ "," + ui->line_planecoef_d->text();
    std::string text = ui->line_planecoef_a->text().toStdString() + "," + ui->line_planecoef_b->text().toStdString()+ "," + ui->line_planecoef_c->text().toStdString()+ "," + ui->line_planecoef_d->text().toStdString();
    std::string name = "planecoef";
    camview->DrawTextAtPoint(point, 0.5, 1.0, 0.0, 0.0, text, name);

}

// // // //


void MainWindow::on_bt_calchistogram_clicked()
{
    qDebug() << "on_bt_calchistogram_clicked";

    histcalc->CalculateHistogram(pctrans->GetRawPointCloud());

}


void MainWindow::on_bt_savehistimg_clicked()
{
    QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(currentSelectingPlyIndex);
    //ui->prefiximg_lineEdit->text();
    QString filename = ui->line_prefiximg->text() + item->text(0).section('.',0,0) + ".jpg";
    std::cout << "histogram img filename " << filename.toStdString() << std::endl;


    cv::imwrite( filename.toStdString(), shown_hist_image );
    cv::destroyWindow("Histogram image");
}


void MainWindow::on_bt_voxelfilter_clicked()
{
    double grid_size = ui->line_voxelfilter->text().toDouble();

    qDebug() << "points before voxel grid " << ui->line_voxelfilter->text()<< " : " << pctrans->GetRawPLYSize();

    pctrans->FilterVoxelSize(grid_size);

    qDebug() << "points after voxel grid " << ui->line_voxelfilter->text()<< " : " << pctrans->GetRawPLYSize();

    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());

    //ui->label_in_pointsize->setText(QLocale(QLocale::English).toString(pctrans->GetRawPLYSize()));//add comma to number

}


void MainWindow::on_bt_outlierremove_clicked()
{
    int meank = ui->line_outlier_meank->text().toInt();
    double stddist = ui->line_outlier_stddist->text().toDouble();

    qDebug() << "points before outlierremove " << ui->line_outlier_meank->text()<< ", " << ui->line_outlier_stddist->text() << " : " << pctrans->GetRawPLYSize();

    pctrans->StatisticalOutlierRemoval(meank,stddist);

    qDebug() << "points after outlierremove " << ui->line_outlier_meank->text()<< ", " << ui->line_outlier_stddist->text() << " : " << pctrans->GetRawPLYSize();

    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());

    //ui->label_in_pointsize->setText(QLocale(QLocale::English).toString(pctrans->GetRawPLYSize()));//add comma to number
}

void MainWindow::on_bt_setpointorigin_clicked()
{


    Eigen::Vector3f masscenter = pctrans->CalculateMassCenterVoxel(0.2);

    qDebug() << "previous masscenter = " << masscenter[0]<< ", " << masscenter[1] << ", " << masscenter[2];


    PointTypeXYZRGB point1,point2;
    point1.x=masscenter[0];
    point1.y=masscenter[1];
    point1.z=masscenter[2];
    point2.x=0;
    point2.y=0;
    point2.z=0;
    pctrans->MovePointCloudFromTo(point1,point2);

    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());

}


void MainWindow::on_bt_test1_clicked()
{
    //QTime timecounter;
    //timecounter.start();



    //int nMilliseconds = timecounter.elapsed();
    //cout << "CalculateMassCenter timer elapsed " << nMilliseconds << " msec" << endl;
}

void MainWindow::on_bt_test2_clicked()
{

    //QTime timecounter;
    //timecounter.start();



    //int nMilliseconds = timecounter.elapsed();
    //cout << "CalculateMassCenterVoxel = "  << grid_size<< ", timer elapsed " << nMilliseconds << " msec" << endl;
}

void MainWindow::on_pushButton_3_clicked()
{

}


