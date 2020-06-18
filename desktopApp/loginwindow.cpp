#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include <QApplication>


loginWindow::loginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    devicelistWindow = new devicelistwindow();
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::setCommandHandle(std::shared_ptr<CameraControl> camera){
    handle = camera;
    return;
}

void loginWindow::on_deviceSearchButton_clicked()
{
    std::cout<<"current text:"<< ui->connectComboBox->currentText().toStdString()<<std::endl;
    std::string currentConnectMode = ui->connectComboBox->currentText().toStdString();
    if (std::strncmp(currentConnectMode.c_str(), "AP mode", 7) == 0){
        handle->SetCameraIP(handle->GetCameraDefaultIP());
        handle->init();

        MainWindow* masterPage;
        masterPage = new MainWindow();
        masterPage->init();
        masterPage->setCommandHandle(handle);
        masterPage->show();
        this->hide();
        std::cout<<"ap mode connected"<<std::endl;
    } else {
        std::cout<<"station mode connected"<<std::endl;
        std::vector<std::string> device_addr = handle->DeviceSearch();
        devicelistWindow->deviceListShow(device_addr);
    }
}

