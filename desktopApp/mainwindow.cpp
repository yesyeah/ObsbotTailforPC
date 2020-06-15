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

void MainWindow::init(){
    ItemModel = new QStandardItemModel(this);
    handle = nullptr;
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

    std::string zoom = handle->CameraZoomGet();
    std::cout<<"zoom:" << zoom<<std::endl;

    zoom = zoom.substr(0, zoom.find("x"));
    std::cout<<"zoom:" << zoom<<std::endl;

    int presetLocationId  = handle->GimbalPresetLocationAdd((float)atof(zoom.c_str()), location->roll, location->pitch, location->yaw);

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
}

void MainWindow::triggerPresetLocation(QModelIndex id){
    std::cout<<"trigger a location:"<<id.column()<<std::endl;
    handle->GimbalPresetLocationTigger(id.column());
    return ;
}


void MainWindow::on_gimbalResetButton_clicked()
{
    handle->GimbalLocationReset();
}

void MainWindow::on_autoTrackingButton_clicked(bool checked)
{
    if (checked){
        handle->GimbalLock(checked);
    }else{
        handle->GimbalLock(!checked);
    }
}

void MainWindow::on_zoomButton_clicked()
{
    handle->CameraZoomTigger();
}
