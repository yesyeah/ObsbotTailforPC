#ifndef NETCFGDIALOG_H
#define NETCFGDIALOG_H

#include <QDialog>
#include "cameracontrol.h"
namespace Ui {
class NetCfgDialog;
}

class NetCfgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetCfgDialog(QWidget *parent = nullptr);
    ~NetCfgDialog();

    void setCommandHandle(std::shared_ptr<CameraControl> camera);


private slots:
    void on_pushButton_clicked();

private:
    Ui::NetCfgDialog *ui;
    std::shared_ptr<CameraControl> handle;
};

#endif // NETCFGDIALOG_H
