#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include <QApplication>


loginWindow::loginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
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
    MainWindow masterPage;
    masterPage.show();
}

