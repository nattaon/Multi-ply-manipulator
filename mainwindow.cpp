#include "mainwindow.h"
#include "build/ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    camview = new CameraviewTransform();
    pctrans = new PointcloudTransform();
    histcalc = new HistogramCalculation();

    rotation_vector_x = Eigen::Matrix<float, 1, 3>(1.0, 0.0, 0.0);
    rotation_vector_y = Eigen::Matrix<float, 1, 3>(0.0, 1.0, 0.0);
    rotation_vector_z = Eigen::Matrix<float, 1, 3>(0.0, 0.0, 1.0);


    //Show list of ply files
    //currentlyOpenedDir ="/home/okuboali/nattaon_ws/_0room_dataset/nattaon_edited_sceneNN/rotated";
    //currentPlyDir = QString("%1home%1nattaon%1ply%1OriginalPointCloud").arg(QDir::separator());
    currentPlyDir = QString("../ply").arg(QDir::separator());
    ui->line_plyfoldername->setText(currentPlyDir);
    ListPlyInFolder();

    // auto select first index + show pointcloud
    currentSelectingPlyIndex=0;
    QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(currentSelectingPlyIndex);
    on_plyfiles_treeWidget_itemClicked(item,0); // call treeWidget_itemClicked(QTreeWidgetItem *item, int column)
    ui->plyfiles_treeWidget->setCurrentItem(item);

    //to stretch the horizontal scrollbar
    ui->plyfiles_treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->plyfiles_treeWidget->header()->setStretchLastSection(false);


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
        camview->Resetview();
        camview->SetViewUp();

        int pointsize = pctrans->GetRawPLYSize();
        ui->label_in_pointsize->setText(QLocale(QLocale::English).toString(pointsize));//add comma to number

        //QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(currentSelectingPlyIndex);
        QString filename_noext = item->text(0).section('.',0,0);
        ui->line_histnameimg->setText(filename_noext);

        ui->line_postfiximg->setText("");


        qDebug() << "is_dense " << pctrans->GetRawPointCloud()->is_dense;
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
    pctrans->ApplyRotation(rotate_x,rotation_vector_x);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
}

void MainWindow::on_bt_yrot_clicked()
{
    double rotate_y = ui->line_y_rot->text().toDouble();
    pctrans->ApplyRotation(rotate_y,rotation_vector_y);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
}

void MainWindow::on_bt_zrot_clicked()
{
    double rotate_z = ui->line_z_rot->text().toDouble();
    pctrans->ApplyRotation(rotate_z,rotation_vector_z);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
}
void MainWindow::on_bt_xrot_minus_clicked()
{
    pctrans->ApplyRotation(-1.0,rotation_vector_x);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex());
}

void MainWindow::on_bt_xrot_plus_clicked()
{
    pctrans->ApplyRotation(1.0,rotation_vector_x);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex());
}

void MainWindow::on_bt_yrot_minus_clicked()
{
    pctrans->ApplyRotation(-1.0,rotation_vector_y);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex());
}

void MainWindow::on_bt_yrot_plus_clicked()
{
    pctrans->ApplyRotation(1.0,rotation_vector_y);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex());
}

void MainWindow::on_bt_zrot_minus_clicked()
{
    pctrans->ApplyRotation(-1.0,rotation_vector_z);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex());
}
void MainWindow::on_bt_zrot_plus_clicked()
{
    pctrans->ApplyRotation(1.0,rotation_vector_z);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex());
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




void MainWindow::on_bt_voxelfilter_clicked()
{
    double grid_size = ui->line_voxelfilter->text().toDouble();

    qDebug() << "points before voxel grid " << ui->line_voxelfilter->text()<< " : " << pctrans->GetRawPLYSize();

    pctrans->FilterVoxelSize(grid_size);

    qDebug() << "points after voxel grid " << ui->line_voxelfilter->text()<< " : " << pctrans->GetRawPLYSize();

    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());

    int pointsize = pctrans->GetRawPLYSize();
    ui->label_in_pointsize->setText(QLocale(QLocale::English).toString(pointsize));//add comma to number

}


void MainWindow::on_bt_outlierremove_clicked()
{
    int meank = ui->line_outlier_meank->text().toInt();
    double stddist = ui->line_outlier_stddist->text().toDouble();

    qDebug() << "points before outlierremove " << ui->line_outlier_meank->text()<< ", " << ui->line_outlier_stddist->text() << " : " << pctrans->GetRawPLYSize();

    pctrans->StatisticalOutlierRemoval(meank,stddist);

    qDebug() << "points after outlierremove " << ui->line_outlier_meank->text()<< ", " << ui->line_outlier_stddist->text() << " : " << pctrans->GetRawPLYSize();

    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());

    int pointsize = pctrans->GetRawPLYSize();
    ui->label_in_pointsize->setText(QLocale(QLocale::English).toString(pointsize));//add comma to number
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

// to move pointcloud to 0,0,0 position (for all pointclound in the opening folder)
void MainWindow::on_actionSet_points_origin_whole_folder_triggered()
{

    int totalfiles = ui->plyfiles_treeWidget->topLevelItemCount();
    qDebug() << "on_actionSet_points_origin_whole_folder_triggered totalfiles " << totalfiles;

    if(totalfiles==0) return;

    Eigen::Vector3f masscenter;
    PointTypeXYZRGB point1,point2;
    //bool saveresult;

    for (int i = 0; i < totalfiles; ++i) // run through each image file show in the widget
    {
        QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(i);
        QString filename = currentPlyDir + QDir::separator() + item->text(0); //concat ply filename path

        if(pctrans->loadPLY(filename))
        {
            //pctrans->GetRawPointCloud();
            masscenter = pctrans->CalculateMassCenterVoxel(0.2);

            point1.x=masscenter[0];
            point1.y=masscenter[1];
            point1.z=masscenter[2];
            point2.x=0;
            point2.y=0;
            point2.z=0;
            pctrans->MovePointCloudFromTo(point1,point2);
            qDebug() << filename << " size" << pctrans->GetRawPLYSize();

            pctrans->savePLY(filename); //overwrite

        }
    }
}

//  ------------------------------------------------------------------------ //

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


//  ------------------------------------------------------------------------ //



void MainWindow::on_bt_calchistogram_clicked()
{
    qDebug() << "on_bt_calchistogram_clicked "<< ui->comboBox_colormap->currentText();
    //ui->comboBox_colormap->currentIndex()

    histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex());



}


void MainWindow::on_bt_savehistimg_clicked()
{

    QString filename = ui->line_prefiximg->text() + ui->line_histnameimg->text() + ui->line_postfiximg->text();
    QString path_histograme_img = currentPlyDir + QDir::separator() + "histograme";
    QString path_histograme_log = currentPlyDir + QDir::separator() + "histo_log";

    QDir dir;
    dir = QDir(path_histograme_img);
    if (!dir.exists())
        dir.mkpath(".");

    dir = QDir(path_histograme_log);
    if (!dir.exists())
        dir.mkpath(".");

    QString filepath_png = path_histograme_img +  QDir::separator() + filename + ".png";
    QString filepath_txt = path_histograme_log +  QDir::separator() + filename + ".txt";
    //QString filepath_norm_ply = path_histograme_log +  QDir::separator() + filename + "_norm.ply";
    //QString filepath_scale_ply = path_histograme_log +  QDir::separator() + filename + "_scale.ply";



    std::cout << "histogram img filename " << filepath_png.toStdString() << std::endl;

    // check if file exist
    if(QFile::exists(filepath_png))
    {
        QMessageBox::information(this, "File exist!", filepath_png+" is exist.");
    }
    else
    {
        histcalc->SaveHistogramImage(filepath_png.toStdString());
        histcalc->SaveHistogrameLogTextFile(filepath_txt);

        //histcalc->savePLY_cloud_norm(filepath_norm_ply);
        //histcalc->savePLY_cloud_scale(filepath_scale_ply);

    }




}


//  ------------------------------------------------------------------------ //



void MainWindow::on_bt_histgraph1_clicked()
{

}

void MainWindow::on_bt_histgraph2_clicked()
{

}



//  ------------------------------------------------------------------------ //





