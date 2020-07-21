#include "netcfgdialog.h"
#include "ui_netcfgdialog.h"

NetCfgDialog::NetCfgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetCfgDialog)
{
    ui->setupUi(this);
}

NetCfgDialog::~NetCfgDialog()
{
    delete ui;
}

void NetCfgDialog::setCommandHandle(std::shared_ptr<CameraControl> camera){
    handle = camera;
}

void NetCfgDialog::on_pushButton_clicked()
{
    std::string ssid = ui->wifiSSIDEdit->text().toStdString();
    std::string password = ui->wifiPasswordEdit->text().toStdString();

    handle->WifiStatusSet(false, ssid, password);
}
