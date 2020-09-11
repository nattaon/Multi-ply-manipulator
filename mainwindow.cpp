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
    pctrans->ApplyPlaneSegmentation(planeseg_threshold);
    camview->ShowRawPointCloud(pctrans->GetRawPointCloud());
    qDebug() << "remain points " << pctrans->GetRawPLYSize();
}


// // // //



void MainWindow::on_bt_aabb_clicked()
{
    qDebug() << "on_bt_aabb_clicked";
}
void MainWindow::on_bt_calchistogram_clicked()
{
    qDebug() << "on_bt_calchistogram_clicked";
}











