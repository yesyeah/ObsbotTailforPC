#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(std::shared_ptr<CameraControl> camera){
    ItemModel = new QStandardItemModel(this);
    handle = camera;

    if (handle->CameraAutoZoomGet()){
        ui->zoomAddButton->setEnabled(false);
        ui->zoomReduceButton->setEnabled(false);
        ui->zoomButton->setEnabled(false);
        ui->autoZoomButton->setText("打开");
    } else {
        ui->zoomAddButton->setEnabled(true);
        ui->zoomReduceButton->setEnabled(true);
        ui->zoomButton->setEnabled(true);
        ui->autoZoomButton->setText("关闭");
    }

    if (handle->AITrackingGet()){
        ui->autoTrackingButton->setText("打开");
        std::cout<<"auto tracking is  on "<<std::endl;
    } else {
        ui->autoTrackingButton->setText("关闭");
        std::cout<<"auto tracking is  off "<<std::endl;

    }
    if (handle->AIHandposeGet()){
        ui->handPoseButton->setText("打开");
    } else {
        ui->handPoseButton->setText("关闭");
    }

    if (!handle->AIDefaultViewGet()){
        //default view landscape
        ui->objectDefaultViewButton->setText("横屏");
        std::cout<<"default view  is  landscape "<<std::endl;

    } else {
        std::cout<<"default view is not landscape "<<std::endl;
        ui->objectDefaultViewButton->setText("竖屏");
    }

   // showPresetLocation();
}

void MainWindow::setCommandHandle(std::shared_ptr<CameraControl> camera){
    handle = camera;
    return;
}

void MainWindow::on_presetLocationAddButton_clicked()
{
    if (handle == nullptr){
        std::cout<< "camera ctl handle is null"<<std::endl;
    }
    std::shared_ptr<GimbalLocation> location = handle->CameraDirectionGet();
    std::cout<<"roll:" << location->roll <<" pitch:"<<location->pitch <<" yaw:"<<location->yaw<<std::endl;

    std::string zoom = handle->GetAbsZoom();
    std::cout<<"zoom:" << zoom<<std::endl;

    zoom = zoom.substr(0, zoom.find("x"));
    std::cout<<"zoom:" << zoom<<std::endl;

    handle->GimbalPresetLocationAdd((float)atof(zoom.c_str()), location->roll, location->pitch, location->yaw);

    std::string presetLocationItem = "ratio:" + zoom + "     " +
                                     "roll:" + std::to_string(location->roll) + "     " +
                                     "pitch:" + std::to_string(location->pitch) + "     " +
                                     "yaw:" + std::to_string(location->yaw) + "     ";
    std::cout<<"presetLocationgItem:" << presetLocationItem<<std::endl;
    QString presetLocationStr = QString::fromStdString(presetLocationItem);

    QStringList presetLocationList;
    presetLocationList.append(presetLocationStr);

    QStandardItem *item = new QStandardItem(presetLocationStr);
    ItemModel->appendRow(item);
    ui->presetLocationValueList->setModel(ItemModel);
    ui->presetLocationValueList->setFixedWidth(311);

    connect(ui->presetLocationValueList, SIGNAL(clicked(QModelIndex)), this, SLOT(triggerPresetLocation(QModelIndex)));
    //ui->presetLocationValueList->clicked.connect(triggerPresetLocation);
}

void MainWindow::triggerPresetLocation(QModelIndex id){
    std::cout<<"trigger a location:"<<id.row()<<std::endl;
    handle->GimbalPresetLocationTigger(id.row());
    return ;
}

void MainWindow::showPresetLocation(){
    std::cout<<"show preset location:"<<std::endl;
    if (handle == nullptr){
        std::cout<< "camera ctl handle is null"<<std::endl;
    }
    std::vector<GimbalPresetLocation> locations = handle->GimbalPresetLocationGet();

    for (unsigned long long i  = 0; i < locations.size(); i++){
        std::cout<<"id:" << locations[i].id <<"roll:" << locations[i].roll <<" pitch:"<<locations[i].pitch <<" yaw:"<<locations[i].yaw<<std::endl;
        std::string presetLocationItem = "ratio:" + std::to_string(locations[i].zoom) + "     " +
                                         "roll:" + std::to_string( locations[i].roll) + "     " +
                                         "pitch:" + std::to_string(locations[i].pitch) + "     " +
                                         "yaw:" + std::to_string(locations[i].yaw) + "     ";

        std::cout<<"presetLocationgItem:" << presetLocationItem<<std::endl;
        QString presetLocationStr = QString::fromStdString(presetLocationItem);

        QStringList presetLocationList;
        presetLocationList.append(presetLocationStr);

        QStandardItem *item = new QStandardItem(presetLocationStr);
        ItemModel->appendRow(item);
        delete item;

    }

    ui->presetLocationValueList->setModel(ItemModel);
    ui->presetLocationValueList->setFixedWidth(311);

    connect(ui->presetLocationValueList, SIGNAL(clicked(QModelIndex)), this, SLOT(triggerPresetLocation(QModelIndex)));
    //ui->presetLocationValueList->clicked.connect(triggerPresetLocation);
}

void MainWindow::on_gimbalResetButton_clicked()
{
    handle->GimbalLocationReset();
}

void MainWindow::on_zoomButton_clicked()
{
    handle->CameraZoomTigger();
}

void MainWindow::on_gimbalUpButton_clicked()
{
    handle->CameraDirectionSet(0, -3);
}

void MainWindow::on_gimbalLeftButton_clicked()
{
    handle->CameraDirectionSet(5, 0);
}

void MainWindow::on_gimbalDownButton_clicked()
{
    handle->CameraDirectionSet(0, 3);
}

void MainWindow::on_gimbalRightButton_clicked()
{
    handle->CameraDirectionSet(-5, 0);
}

void MainWindow::on_zoomAddButton_clicked()
{
    handle->CameraZoomSet(5);
}

void MainWindow::on_zoomReduceButton_clicked()
{
    handle->CameraZoomSet(-5);
}

void MainWindow::on_autoTrackingButton_clicked()
{
    bool trackingStatus = handle->AITrackingGet();
    if (!trackingStatus){
        ui->autoTrackingButton->setText("打开");
        std::cout<<"auto tracking is  on "<<std::endl;
    } else {
        ui->autoTrackingButton->setText("关闭");
        std::cout<<"auto tracking is  off "<<std::endl;

    }
    handle->AITrackingSet(!trackingStatus);
}

void MainWindow::on_handPoseButton_clicked()
{
    bool handPoseStatus = !handle->AIHandposeGet();
    if (handPoseStatus){
        ui->handPoseButton->setText("打开");
        std::cout<<"hand pose is  on "<<std::endl;

    } else {
        ui->handPoseButton->setText("关闭");
        std::cout<<"hande pose is  off "<<std::endl;

    }
    handle->AIHandposeSet(handPoseStatus);
}

void MainWindow::on_autoZoomButton_clicked()
{
    bool currentZoomStatus = handle->CameraAutoZoomGet();
    if (!currentZoomStatus){
        //auto zoom status disable  handzoom
        ui->zoomAddButton->setEnabled(false);
        ui->zoomReduceButton->setEnabled(false);
        ui->zoomButton->setEnabled(false);
        ui->autoZoomButton->setText("打开");
        std::cout<<"auto zomm is  on "<<std::endl;

    } else {
        //enable hand zoom
        ui->zoomAddButton->setEnabled(true);
        ui->zoomReduceButton->setEnabled(true);
        ui->zoomButton->setEnabled(true);
        std::cout<<"auto zoom is  off "<<std::endl;
        ui->autoZoomButton->setText("关闭");
    }
    handle->CameraAutoZoomSet(!currentZoomStatus);
}

void MainWindow::on_uvcButton_clicked(){

}

void MainWindow::on_objectDefaultViewButton_clicked(){
    bool currentDefaultView = handle->AIDefaultViewGet();
    if (!currentDefaultView){
        //default view landscape
        ui->objectDefaultViewButton->setText("横屏");
        std::cout<<"default view  is  landscape "<<std::endl;

    } else {
        std::cout<<"default view is not landscape "<<std::endl;
        ui->objectDefaultViewButton->setText("竖屏");
    }
    handle->AIDefaultViewSet(!currentDefaultView);
}
