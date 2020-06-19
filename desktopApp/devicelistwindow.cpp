#include "devicelistwindow.h"
#include "ui_devicelistwindow.h"

devicelistwindow::devicelistwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::devicelistwindow)
{
    ui->setupUi(this);
    ItemModel = new QStandardItemModel(this);
}

devicelistwindow::~devicelistwindow()
{
    delete ui;
}

bool devicelistwindow::deviceListShow(std::vector<std::string> info_list){
    QStringList presetLocationList;

    for (std::string device_info : info_list){
        QString device = QString::fromStdString(device_info);
        presetLocationList.append(device);
        QStandardItem *item = new QStandardItem(device);
        ItemModel->appendRow(item);

        ui->deviceList->setModel(ItemModel);
        ui->deviceList->setFixedWidth(311);
    }
    connect(ui->deviceList, SIGNAL(clicked(QModelIndex)), this, SLOT(triggerPresetLocation(QModelIndex)));
    return true;
}

void devicelistwindow::connectTodevice(QModelIndex id){

}


