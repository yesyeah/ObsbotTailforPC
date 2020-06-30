#ifndef DEVICELISTWINDOW_H
#define DEVICELISTWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include "mainwindow.h"

namespace Ui {
class devicelistwindow;
}

class devicelistwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit devicelistwindow(QWidget *parent = nullptr);
    ~devicelistwindow();

    bool deviceListShow(std::vector<std::string> info_list);
    void setCommandHandle(std::shared_ptr<CameraControl> camera);
private slots:
    void connectTodevice(QModelIndex id);

private:
    Ui::devicelistwindow *ui;
    MainWindow* masterPage;

    QStringListModel *Model;
    QStandardItemModel *ItemModel;
    std::shared_ptr<CameraControl> handle;


};

#endif // DEVICELISTWINDOW_H
