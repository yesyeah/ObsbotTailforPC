#include "devicelistwindow.h"
#include "ui_devicelistwindow.h"

devicelistwindow::devicelistwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::devicelistwindow)
{
    ui->setupUi(this);
    ItemModel = new QStandardItemModel(this);
    masterPage = new MainWindow();

    //deviceListShow();
}

devicelistwindow::~devicelistwindow()
{
    delete ui;
    delete masterPage;
}

void devicelistwindow::setCommandHandle(std::shared_ptr<CameraControl> camera){
    handle = camera;
    return;
}


bool devicelistwindow::deviceListShow(std::vector<std::string> info_list){
    QStringList presetLocationList;

    for (std::string device_info : info_list){
        QString device = QString::fromStdString(device_info);
        presetLocationList.append(device);
        QStandardItem *item = new QStandardItem(device);
        ItemModel->appendRow(item);
    }

    ui->deviceList->setModel(ItemModel);
    ui->deviceList->setFixedWidth(311);
    connect(ui->deviceList, SIGNAL(clicked(QModelIndex)), this, SLOT(connectTodevice(QModelIndex)));
    return true;
}

void devicelistwindow::connectTodevice(QModelIndex id){
    std::cout<<"set camera ip as "<<id.data().toString().toStdString()<<std::endl;
    handle->SetCameraIP(id.data().toString().toStdString());
    masterPage->init(handle);
    masterPage->show();
    this->hide();
}


