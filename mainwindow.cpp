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

    on_radioButton_bg_white_clicked();


    int A[4] = {0, 2, 3, 1};
    const int N = sizeof(A) / sizeof(int);
    std::cout << "A " << A << std::endl;
    std::cout << "N " << N << std::endl;

    std::cout << "Index of max element: "
         << std::distance(A, std::max_element(A, A + N))
         << std::endl;


    //Show list of ply files
    //currentlyOpenedDir ="/home/okuboali/nattaon_ws/_0room_dataset/nattaon_edited_sceneNN/rotated";
    //currentPlyDir = QString("%1home%1nattaon%1ply%1OriginalPointCloud").arg(QDir::separator());
    //currentPlyDir = QString("../ply").arg(QDir::separator());
    //currentPlyDir="/home/nattaon/ply/beike-ply";
    //currentPlyDir="/home/okuboali/nattaon_ws/_0room_dataset/beike/beike-ply/aligned";
    //currentPlyDir="/home/nattaon/ply/color_ply0all";
    //currentPlyDir="/home/nattaon/ply/aligned-sceneNN-voxel";
    //currentPlyDir="/home/nattaon/data_room_ply/aligned-sceneNN-voxel-01";  //standford+pablo
    //currentPlyDir="/home/nattaon/data_room_ply/Stanford_ply_voxel05";
    //currentPlyDir="/home/nattaon/github/Structured3D";
    currentPlyDir="/home/nattaon/data_room_ply/scan2bim_PabloHouse/v02";
    ui->line_plyfoldername->setText(currentPlyDir);

    ListPlyInFolder();

    // auto select first index + show pointcloud
    currentSelectingPlyIndex=0;
    QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(currentSelectingPlyIndex);
    //on_plyfiles_treeWidget_itemClicked(item,0); // call treeWidget_itemClicked(QTreeWidgetItem *item, int column)
    //ui->plyfiles_treeWidget->setCurrentItem(item);

    //to stretch the horizontal scrollbar, otherwise no scrollbar shown
    ui->plyfiles_treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->plyfiles_treeWidget->header()->setStretchLastSection(false);

    //int *histogram_arr = new int[1500*1500];

    ui->comboBox_colormap->setCurrentIndex(7); // [7]PlasmaMod

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
        camview->RotateViewUp();

        int pointsize = pctrans->GetRawPLYSize();
        ui->label_in_pointsize->setText(QLocale(QLocale::English).toString(pointsize));//add comma to number

        //QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(currentSelectingPlyIndex);
        filename_noext = item->text(0).section('.',0,0);
        ui->line_histnameimg->setText(filename_noext);

        ui->line_prefiximg->setText("");
        ui->line_postfiximg->setText("");


        qDebug() << "is_dense " << pctrans->GetRawPointCloud()->is_dense;
        if(ui->checkBox_autocalchist->isChecked())
            on_bt_calchistogram_clicked();//show histogram
        //on_bt_test2_clicked(); //show rotation guide
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
    //QString filename_noext = item->text(0).section('.',0,0);
    QString postfix = ui->line_postfix_ply->text();

    QString suggestionname = currentPlyDir + QDir::separator() + filename_noext + postfix + ".ply"; //concat ply filename path
    //QString filename = QFileDialog::getSaveFileName(this, tr ("Save .ply"), suggestionname, tr ("Pointcloud file(*.ply)"));
/*
    //PCL_INFO("File chosen: %s\n", filename.toStdString().c_str ());
    if(QFile::exists(suggestionname))
    {
        QMessageBox::information(this, "File exist!", suggestionname+" is exist.");
    }
    else
    {
        bool saveresult = pctrans->savePLY(suggestionname);
        qDebug() <<  saveresult <<" : Save "<< suggestionname ;
    }
 */
    // check if file exist
    bool saveresult;
    if(QFile::exists(suggestionname))
    {

        QMessageBox msgBox;
        msgBox.setText("File name "+suggestionname+" is exist.");
        msgBox.setInformativeText("Do you want to overwrite?");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::No);

        int ret = msgBox.exec();
        switch (ret)
        {
          case QMessageBox::Yes:
            saveresult = pctrans->savePLY(suggestionname);
            qDebug() <<  saveresult <<" : Save "<< suggestionname;
              break;

          case QMessageBox::No:
              // Don't Save was clicked
              break;

          default:
              // should never be reached
              break;
        }

    }
    else
    {
        saveresult = pctrans->savePLY(suggestionname);
        qDebug() <<  saveresult <<" : Save "<< suggestionname ;
    }


}


// // CAMERA VIEW ///

void MainWindow::on_bt_resetcam_clicked()
{
    camview->Resetview();

}
void MainWindow::on_bt_viewup_clicked()
{
    camview->RotateViewUp();
}

void MainWindow::on_bt_viewdown_clicked()
{
    camview->RotateViewDown();
}

void MainWindow::on_bt_viewleft_clicked()
{
    camview->RotateViewLeft();
}

void MainWindow::on_bt_viewright_clicked()
{
    camview->RotateViewRight();
}

// // POINTCLOUD MANIPULATION ///

void MainWindow::on_bt_xrot_clicked()
{
    double rotate_x = ui->line_x_rot->text().toDouble();
    pctrans->ApplyRotation(rotate_x,rotation_vector_x);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        on_bt_calchistogram_clicked();
}

void MainWindow::on_bt_yrot_clicked()
{
    double rotate_y = ui->line_y_rot->text().toDouble();
    pctrans->ApplyRotation(rotate_y,rotation_vector_y);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        on_bt_calchistogram_clicked();
}

void MainWindow::on_bt_zrot_clicked()
{
    double rotate_z = ui->line_z_rot->text().toDouble();
    pctrans->ApplyRotation(rotate_z,rotation_vector_z);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        on_bt_calchistogram_clicked();
}
void MainWindow::on_bt_xrot_minus_clicked()
{
    pctrans->ApplyRotation(-1.0,rotation_vector_x);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        on_bt_calchistogram_clicked();
}

void MainWindow::on_bt_xrot_plus_clicked()
{
    pctrans->ApplyRotation(1.0,rotation_vector_x);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        on_bt_calchistogram_clicked();
}

void MainWindow::on_bt_yrot_minus_clicked()
{
    pctrans->ApplyRotation(-1.0,rotation_vector_y);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        on_bt_calchistogram_clicked();
}

void MainWindow::on_bt_yrot_plus_clicked()
{
    pctrans->ApplyRotation(1.0,rotation_vector_y);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        on_bt_calchistogram_clicked();
}

void MainWindow::on_bt_zrot_minus_clicked()
{
    pctrans->ApplyRotation(-1.0,rotation_vector_z);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        on_bt_calchistogram_clicked();
}
void MainWindow::on_bt_zrot_plus_clicked()
{
    pctrans->ApplyRotation(1.0,rotation_vector_z);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    if(ui->checkBox_autocalchist->isChecked())
        on_bt_calchistogram_clicked();
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
    //pctrans->PointcloudAlignAxis();
    on_bt_setpointorigin_clicked();
    show_rotation_guide_360();
    //camview->DrawOBB(pctrans->position_OBB, pctrans->min_point_OBB, pctrans->max_point_OBB, pctrans->rotational_matrix_OBB);
  /*
    camview->DrawSphere(pctrans->min_point_AABB, 0.2, "min_point_AABB");
    camview->DrawSphere(pctrans->max_point_AABB, 0.3, "max_point_AABB");

    camview->DrawBoundingBox(pctrans->min_point_AABB.x, pctrans->max_point_AABB.x,
                             pctrans->min_point_AABB.y, pctrans->max_point_AABB.y,
                           pctrans->min_point_AABB.z, pctrans->max_point_AABB.z);

        */
    //QTime timecounter;
    //timecounter.start();



    //int nMilliseconds = timecounter.elapsed();
    //cout << "CalculateMassCenter timer elapsed " << nMilliseconds << " msec" << endl;
}
void MainWindow::on_bt_test2_clicked()
{
    show_rotation_guide_360();
}


void MainWindow::show_rotation_guide_360()
{
    PointTypeXYZ p1,p2;
    p1.x=0; p1.y=0; p1.z=0;

    Eigen::Vector3f p2vec;

    for(int deg =10;deg<81;deg+=10)
    {
        //cout << "azix pos at deg=" << deg <<" = " << 2*tan(deg*M_PI/180) <<endl;
        p2vec[0]=1; p2vec[1]=0; p2vec[2]=tan(deg*M_PI/180);
        p2vec.normalize();
        p2vec*=4; //scale up the line

        p2.x=p2vec[0]; p2.y=p2vec[1]; p2.z=p2vec[2];

        camview->DrawLine(p1,p2,"line_left_up"+ std::to_string(deg));
        p2.x*=-1;
        camview->DrawLine(p1,p2,"line_right_up"+ std::to_string(deg));
        p2.z*=-1;
        camview->DrawLine(p1,p2,"line_right_down"+ std::to_string(deg));
        p2.x*=-1;
        camview->DrawLine(p1,p2,"line_left_down"+ std::to_string(deg));
    }
}



void MainWindow::on_pushButton_3_clicked()
{

}


//  ------------------------------------------------------------------------ //



void MainWindow::on_bt_calchistogram_clicked()
{
    //qDebug() << "\n on_bt_calchistogram_clicked, colormap:"<< ui->comboBox_colormap->currentText();
    //ui->comboBox_colormap->currentIndex()



    //Eigen::Vector3f masscenter = pctrans->CalculateMassCenterVoxel(0.2);
    //std::cout << masscenter << std::endl;
    int imgwidth,imgheight,maxdensity;
    histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex(),imgwidth,imgheight,maxdensity);

    ui->label_in_imgsize->setText(QString::number(imgwidth)+"*"+QString::number(imgheight));
    ui->label_in_maxdensity->setText(QString::number(maxdensity));
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

void MainWindow::on_bt_histgraph2_clicked() // loop create slightly rotation of histogram map
{
    int imgwidth,imgheight,maxdensity;
    QString path_histograme_img = currentPlyDir + QDir::separator() + "histograme";
    QString path_histograme_log = currentPlyDir + QDir::separator() + "histo_log";

    //original
    pctrans->ReloadPLY();
    histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex(),imgwidth,imgheight,maxdensity);
    QString filepath_png = path_histograme_img +  QDir::separator() + filename_noext + "_00" + ".png";
    QString filepath_txt = path_histograme_log +  QDir::separator() + filename_noext + "_00" + ".txt";
    histcalc->SaveHistogramImage(filepath_png.toStdString());
    histcalc->SaveHistogrameLogTextFile(filepath_txt);

    float rotVariation[4] = {-2.0, -1.0, 1.0, 2.0};

    QString rotyName[4] = {"_y-2", "_y-1", "_y01", "_y02"};
    for(int i =0; i<sizeof(rotVariation) / sizeof(rotVariation[0]);i++)
    {
        pctrans->ReloadPLY();
        pctrans->ApplyRotation(rotVariation[i],rotation_vector_y);
        histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex(),imgwidth,imgheight,maxdensity);
        QString filepath_png = path_histograme_img +  QDir::separator() + filename_noext + rotyName[i] + ".png";
        QString filepath_txt = path_histograme_log +  QDir::separator() + filename_noext + rotyName[i] + ".txt";
        histcalc->SaveHistogramImage(filepath_png.toStdString());
        //histcalc->SaveHistogrameLogTextFile(filepath_txt);
    }

    QString rotxName[4] = {"_x-2", "_x-1", "_x01", "_x02"};
    for(int i =0; i<sizeof(rotVariation) / sizeof(rotVariation[0]);i++)
    {
        pctrans->ReloadPLY();
        pctrans->ApplyRotation(rotVariation[i],rotation_vector_x);
        histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex(),imgwidth,imgheight,maxdensity);
        QString filepath_png = path_histograme_img +  QDir::separator() + filename_noext + rotxName[i] + ".png";
        QString filepath_txt = path_histograme_log +  QDir::separator() + filename_noext + rotxName[i] + ".txt";
        histcalc->SaveHistogramImage(filepath_png.toStdString());
        //histcalc->SaveHistogrameLogTextFile(filepath_txt);
    }

    QString rotzName[4] = {"_z-2", "_z-1", "_z01", "_z02"};
    for(int i =0; i<sizeof(rotVariation) / sizeof(rotVariation[0]);i++)
    {
        pctrans->ReloadPLY();
        pctrans->ApplyRotation(rotVariation[i],rotation_vector_z);
        histcalc->CalculateHistogram(pctrans->GetRawPointCloud(),ui->comboBox_colormap->currentIndex(),imgwidth,imgheight,maxdensity);
        QString filepath_png = path_histograme_img +  QDir::separator() + filename_noext + rotzName[i] + ".png";
        QString filepath_txt = path_histograme_log +  QDir::separator() + filename_noext + rotzName[i] + ".txt";
        histcalc->SaveHistogramImage(filepath_png.toStdString());
        //histcalc->SaveHistogrameLogTextFile(filepath_txt);
    }

}



//  ------------------------------------------------------------------------ //






void MainWindow::on_bt_setcam_y_front_clicked()
{
    on_bt_resetcam_clicked();
    on_bt_viewup_clicked();
}

void MainWindow::on_bt_getboundary_clicked()
{
    PointTypeXYZRGB minpoint, maxpoint;

    pctrans->GetBounding(minpoint, maxpoint);

    qDebug() << "minpoint" << minpoint.x;
    qDebug() << "maxpoint" << maxpoint.x;

    ui->line_boundary_xmin->setText(QString::number(minpoint.x, 'f', 2));
    ui->line_boundary_xmax->setText(QString::number(maxpoint.x, 'f', 2));

    ui->line_boundary_ymin->setText(QString::number(minpoint.y, 'f', 2));
    ui->line_boundary_ymax->setText(QString::number(maxpoint.y, 'f', 2));

    ui->line_boundary_zmin->setText(QString::number(minpoint.z, 'f', 2));
    ui->line_boundary_zmax->setText(QString::number(maxpoint.z, 'f', 2));

    ui->line_boundary_xbound->setText(QString::number(maxpoint.x-minpoint.x, 'f', 2));
    ui->line_boundary_ybound->setText(QString::number(maxpoint.y-minpoint.y, 'f', 2));
    ui->line_boundary_zbound->setText(QString::number(maxpoint.z-minpoint.z, 'f', 2));

    if(ui->checkBox_copytorange->isChecked())
    {
        ui->line_passthrough_xmin->setText(QString::number(minpoint.x, 'f', 2));
        ui->line_passthrough_xmax->setText(QString::number(maxpoint.x, 'f', 2));

        ui->line_passthrough_ymin->setText(QString::number(minpoint.y, 'f', 2));
        ui->line_passthrough_ymax->setText(QString::number(maxpoint.y, 'f', 2));

        ui->line_passthrough_zmin->setText(QString::number(minpoint.z, 'f', 2));
        ui->line_passthrough_zmax->setText(QString::number(maxpoint.z, 'f', 2));
    }
    if(ui->checkBox_showbounding->isChecked())
    {
        on_bt_show_bounding_clicked();
    }
}


void MainWindow::on_bt_passthroughfilter_xyz_clicked()
{
    on_bt_passthroughfilter_x_clicked();
    on_bt_passthroughfilter_y_clicked();
    on_bt_passthroughfilter_z_clicked();

}


void MainWindow::on_bt_passthroughfilter_x_clicked()
{
    double xmin = ui->line_passthrough_xmin->text().toDouble();
    double xmax = ui->line_passthrough_xmax->text().toDouble();
    pctrans->PassthroughFilter("x",xmin,xmax);

    camview->RemoveBoundingBox();
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    on_bt_getboundary_clicked();
}
void MainWindow::on_bt_passthroughfilter_y_clicked()
{
    double ymin = ui->line_passthrough_ymin->text().toDouble();
    double ymax = ui->line_passthrough_ymax->text().toDouble();
    pctrans->PassthroughFilter("y",ymin,ymax);

    camview->RemoveBoundingBox();
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    on_bt_getboundary_clicked();
}

void MainWindow::on_bt_passthroughfilter_z_clicked()
{
    double zmin = ui->line_passthrough_zmin->text().toDouble();
    double zmax = ui->line_passthrough_zmax->text().toDouble();
    pctrans->PassthroughFilter("z",zmin,zmax);

    camview->RemoveBoundingBox();
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    on_bt_getboundary_clicked();
}


void MainWindow::on_bt_show_bounding_clicked()
{
    double xmin = ui->line_passthrough_xmin->text().toDouble();
    double xmax = ui->line_passthrough_xmax->text().toDouble();
    double ymin = ui->line_passthrough_ymin->text().toDouble();
    double ymax = ui->line_passthrough_ymax->text().toDouble();
    double zmin = ui->line_passthrough_zmin->text().toDouble();
    double zmax = ui->line_passthrough_zmax->text().toDouble();

    camview->DrawBoundingBox(xmin,xmax,ymin,ymax,zmin,zmax);
}

void MainWindow::on_bt_savepointcloudimg_clicked()
{
    QString filename = ui->line_prefiximg->text() + ui->line_histnameimg->text() + ui->line_postfiximg->text();
    QString path_pointcloud_img = currentPlyDir + QDir::separator() + "pointcloudimg";

    QDir dir;
    dir = QDir(path_pointcloud_img);
    if (!dir.exists())
        dir.mkpath(".");



    QString filepath_png = path_pointcloud_img +  QDir::separator() + filename + ".png";


    //std::cout << "histogram img filename " << filepath_png.toStdString() << std::endl;

    // check if file exist
    if(QFile::exists(filepath_png))
    {

        QMessageBox msgBox;
        msgBox.setText("File name "+filepath_png+" is exist.");
        msgBox.setInformativeText("Do you want to overwrite?");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Yes:
              camview->SaveViewerScreenShot(filepath_png.toStdString());
              break;
          case QMessageBox::No:
              // Don't Save was clicked
              break;
          default:
              // should never be reached
              break;
        }

    }
    else
    {
        camview->SaveViewerScreenShot(filepath_png.toStdString());
    }


}

void MainWindow::on_bt_reload_clicked()
{
    pctrans->ReloadPLY();
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    camview->Resetview();
    camview->RotateViewUp();

    int pointsize = pctrans->GetRawPLYSize();
    ui->label_in_pointsize->setText(QLocale(QLocale::English).toString(pointsize));//add comma to number

    //QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(currentSelectingPlyIndex);
    //QString filename_noext = item->text(0).section('.',0,0);
    //ui->line_histnameimg->setText(filename_noext);

    ui->line_prefiximg->setText("");
    ui->line_postfiximg->setText("");

    on_bt_calchistogram_clicked(); //show histogram
}

void MainWindow::on_actionCalc_Hist_xyz_all_triggered()
{

    int totalfiles = ui->plyfiles_treeWidget->topLevelItemCount();
    qDebug() << "on_actionCalc_Hist_xyz_all_triggered totalfiles " << totalfiles;

    if(totalfiles==0) return;

    QString path_histograme_img = currentPlyDir + QDir::separator() + "histograme";
    QString path_histograme_log = currentPlyDir + QDir::separator() + "histo_log";
    QDir dir;
    dir = QDir(path_histograme_img);
    if (!dir.exists())
        dir.mkpath(".");

    dir = QDir(path_histograme_log);
    if (!dir.exists())
        dir.mkpath(".");

    for (int i = 0; i < totalfiles; ++i) // run through each image file show in the widget
    {
        QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(i);
        QString filename = currentPlyDir + QDir::separator() + item->text(0); //concat ply filename path

        if(pctrans->loadPLY(filename))
        {
            filename_noext = item->text(0).section('.',0,0);

            on_bt_histgraph2_clicked();

        }
    }
}

void MainWindow::on_actionVoxel_grid_all_triggered()
{
    int totalfiles = ui->plyfiles_treeWidget->topLevelItemCount();
    qDebug() << "on_actionVoxel_grid_all_triggered totalfiles " << totalfiles;

    for (int i = 0; i < totalfiles; ++i) // run through each image file show in the widget
    {
        QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(i);
        QString filename = currentPlyDir + QDir::separator() + item->text(0); //concat ply filename path

        if(pctrans->loadPLY(filename))
        {

            double grid_size = ui->line_voxelfilter->text().toDouble();
            pctrans->FilterVoxelSize(grid_size);
            pctrans->savePLY(filename); //overwrite




        }
    }
}

void MainWindow::on_radioButton_bg_black_clicked()
{
    camview->SetBGColorBlack();
    ui->radioButton_bg_black->setChecked(true);
    ui->radioButton_bg_white->setChecked(false);
}

void MainWindow::on_radioButton_bg_white_clicked()
{
    camview->SetBGColorWhite();
    ui->radioButton_bg_white->setChecked(true);
    ui->radioButton_bg_black->setChecked(false);
}

void MainWindow::on_bt_apply_windowsize_clicked()
{
   int windown_new_w =  ui->line_windowsize_w->text().toInt();
   int windown_new_h =  ui->line_windowsize_h->text().toInt();
    camview->SetWindowViewSize(windown_new_w,windown_new_h);
}

void MainWindow::on_actionShow_xyz_axis_triggered()
{
    if(ui->actionShow_xyz_axis->isChecked())
    {
        qDebug() << "actionShow_xyz_axis is checked";
        camview->AddCoordinateSystem();
    }
    else
    {
        qDebug() << "actionShow_xyz_axis uncheck";
        camview->RemoveCoordinateSystem();
    }

}
