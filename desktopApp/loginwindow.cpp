#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QApplication>

loginWindow::loginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    devicelistWindow = new devicelistwindow();
    masterPage = new MainWindow();
    netCfgDialog = new NetCfgDialog();

}

loginWindow::~loginWindow()
{
    delete ui;
    delete netCfgDialog;
    delete devicelistWindow;
    delete masterPage;
}

void loginWindow::setCommandHandle(std::shared_ptr<CameraControl> camera){
    handle = camera;
    return;
}

void loginWindow::on_deviceSearchButton_clicked()
{
    devicelistWindow->setCommandHandle(handle);
    std::cout<<"current text:"<< ui->connectComboBox->currentText().toStdString()<<std::endl;
    std::string currentConnectMode = ui->connectComboBox->currentText().toStdString();
    if (std::strncmp(currentConnectMode.c_str(), "AP mode", 7) == 0){
        handle->SetCameraIP(handle->GetCameraDefaultIP());
        if (!handle->isInited()){
            handle->init();
        }
        masterPage->init(handle);
        masterPage->show();
        this->hide();
        std::cout<<"ap mode connected"<<std::endl;
    } else {
        std::cout<<"station mode connected, handle is init "<< handle->isInited()<<std::endl;
        devicelistWindow->show();
        this->hide();
        if (!handle->isInited()){
            handle->init();
        }
        std::vector<std::string> device_addr = handle->DeviceSearch();
        devicelistWindow->deviceListShow(device_addr);
    }
}

void loginWindow::on_cameraNetCfgButton_clicked(){
    handle->SetCameraIP(handle->GetCameraDefaultIP());
    handle->init();
    netCfgDialog->setCommandHandle(handle);
    netCfgDialog->show();
    //this->hide();
    //handle->WifiStatusSet(false);
}
