#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include "cameracontrol.h"
#include "utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init(std::shared_ptr<CameraControl> camera);
    void setCommandHandle(std::shared_ptr<CameraControl> camera);

    QStringListModel *Model;
    QStandardItemModel *ItemModel;

private slots:
    void triggerPresetLocation(QModelIndex id);

    void on_witheBalanceComboBox_currentIndexChanged(const QString &arg1);

    void on_exposeComboBox_currentIndexChanged(const QString &arg1);

    void on_isoComboBox_currentIndexChanged(const QString &arg1);

    void on_presetLocationAddButton_clicked();

    void showPresetLocation();

    void on_gimbalResetButton_clicked();

    void on_gimbalUpButton_clicked();

    void on_gimbalLeftButton_clicked();

    void on_gimbalDownButton_clicked();

    void on_gimbalRightButton_clicked();


    void on_autoTrackingButton_clicked();

    void on_handPoseButton_clicked();

    void on_autoZoomButton_clicked();

    void on_uvcButton_clicked();

    void on_objectDefaultViewButton_clicked();

    void on_pushButton_clicked();

    void on_gimbalUpLeftButton_clicked();

    void on_gimbalUpRightButton_clicked();

    void on_gimbalDownLeftButton_clicked();

    void on_gimbalDownRightButton_clicked();

    void on_zoomSlider_sliderReleased();

    void on_zoomSlider_sliderPressed();

    void on_zoomSlider_sliderMoved(int position);

    void on_powerOffButton_clicked();

    void on_presetLocationAddButton_1_clicked();

    void on_preesetLocationEnable_1_clicked();

    void on_presetLocationAddButton_2_clicked();

    void on_preesetLocationEnable_2_clicked();

    void on_presetLocationAddButton_3_clicked();

    void on_preesetLocationEnable_3_clicked();

    void on_presetLocationAddButton_4_clicked();

    void on_preesetLocationEnable_4_clicked();

    void on_presetLocationDel_1_clicked();

    void on_presetLocationDel_2_clicked();

    void on_preesetLocationDel_3_clicked();

    void on_preesetLocationDel_4_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<CameraControl> handle;

    float currentZoomValue;
};
#endif // MAINWINDOW_H
