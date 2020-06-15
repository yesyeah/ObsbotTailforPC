#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include "cameracontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();
    void setCommandHandle(std::shared_ptr<CameraControl> camera);

    QStringListModel *Model;
    QStandardItemModel *ItemModel;
private slots:
    void on_presetLocationAddButton_clicked();
    void triggerPresetLocation(QModelIndex id);
    void on_gimbalResetButton_clicked();

    void on_autoTrackingButton_clicked(bool checked);

    void on_zoomButton_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<CameraControl> handle;
};
#endif // MAINWINDOW_H
