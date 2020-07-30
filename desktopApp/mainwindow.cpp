#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->powerOffButton->setVisible(false);
    ui->poweroffLabel->setVisible(false);
    ui->uvcLabel->setVisible(false);
    ui->uvcButton->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(std::shared_ptr<CameraControl> camera){
    ItemModel = new QStandardItemModel(this);
    handle = camera;

    if (handle->CameraAutoZoomGet()){
        ui->zoomSlider->setDisabled(true);
        ui->autoZoomButton->setText("打开");
        ui->autoZoomButton->setIcon(QIcon(":/image/icon/on2.png"));

    } else {
        ui->zoomSlider->setDisabled(false);
        ui->autoZoomButton->setText("关闭");
        ui->autoZoomButton->setIcon(QIcon(":/image/icon/off2.png"));
    }

    if (handle->AITrackingGet()){
        ui->autoTrackingButton->setText("打开");
        ui->autoTrackingButton->setIcon(QIcon(":/image/icon/on2.png"));
        ui->pushButton->setEnabled(true);
        std::cout<<"auto tracking is  on "<<std::endl;
    } else {
        ui->autoTrackingButton->setText("关闭");
        ui->autoTrackingButton->setIcon(QIcon(":/image/icon/off2.png"));
        ui->pushButton->setEnabled(false);
        std::cout<<"auto tracking is  off "<<std::endl;
    }
    if (handle->AIHandposeGet()){
        ui->handPoseButton->setIcon(QIcon(":/image/icon/on2.png"));
        ui->handPoseButton->setText("打开");

    } else {
        ui->handPoseButton->setIcon(QIcon(":/image/icon/off2.png"));
        ui->handPoseButton->setText("关闭");
    }

    if (!handle->AIDefaultViewGet()){
        //default view landscape
        ui->objectDefaultViewButton->setText("横屏");
        std::cout<<"default view  is  landscape "<<std::endl;

    } else {
        std::cout<<"default view is not landscape "<<std::endl;
        ui->objectDefaultViewButton->setText("竖屏");
    }

    /*if (handle->CameraUVCModeGet()){
        ui->uvcButton->setIcon(QIcon(":/image/icon/off2.png"));
        ui->uvcButton->setText("关闭");
    }else {
        ui->uvcButton->setIcon(QIcon(":/image/icon/on2.png"));
        ui->uvcButton->setText("打开");
    }

    int value = handle->CameraISOGet();
    ui->isoComboBox->setCurrentText(QString::fromStdString(std::to_string(value)));

    value = handle->CameraExposeGet();
    ui->exposeComboBox->setCurrentText(QString::fromStdString(std::to_string(value)));*/

    currentZoomValue = handle->GetCurrentZoom();

    ui->zoomLabel_2->setText(QString::fromStdString(std::to_string(currentZoomValue)+"x"));

    ui->zoomSlider->setMinimum(0);
    ui->zoomSlider->setMaximum(8);
    ui->zoomSlider->setSingleStep(1);
    ui->zoomSlider->setTickPosition(QSlider::TicksBelow);
    ui->zoomSlider->setTickInterval(1);
    ui->zoomSlider->setValue(currentZoomValue/0.5 -2);

    //ui->exposeComboBox->setEditable(false);

    showPresetLocation();
}

void MainWindow::setCommandHandle(std::shared_ptr<CameraControl> camera){
    handle = camera;
    return;
}

void MainWindow::on_presetLocationAddButton_clicked()
{
    if (handle == nullptr){
        std::cout<< "camera ctl handle is null"<<std::endl;
    }
    std::shared_ptr<GimbalLocation> location = handle->CameraDirectionGet();
    std::cout<<"roll:" << location->roll <<" pitch:"<<location->pitch <<" yaw:"<<location->yaw<<std::endl;

    std::string zoom = handle->GetAbsZoom();
    std::cout<<"zoom:" << zoom<<std::endl;

    zoom = zoom.substr(0, zoom.find("x"));
    std::cout<<"zoom:" << zoom<<std::endl;

    //handle->GimbalPresetLocationAdd((float)atof(zoom.c_str()), location->roll, location->pitch, location->yaw);

    std::string presetLocationItem = "ratio:" + zoom + "     " +
                                     "roll:" + std::to_string(location->roll) + "     " +
                                     "pitch:" + std::to_string(location->pitch) + "     " +
                                     "yaw:" + std::to_string(location->yaw) + "     ";
    std::cout<<"presetLocationgItem:" << presetLocationItem<<std::endl;
    QString presetLocationStr = QString::fromStdString(presetLocationItem);

    QStringList presetLocationList;
    presetLocationList.append(presetLocationStr);

    QStandardItem *item = new QStandardItem(presetLocationStr);
    ItemModel->appendRow(item);
   // ui->presetLocationValueList->setModel(ItemModel);
    //ui->presetLocationValueList->setFixedWidth(311);

   // connect(ui->presetLocationValueList, SIGNAL(clicked(QModelIndex)), this, SLOT(triggerPresetLocation(QModelIndex)));
    //ui->presetLocationValueList->clicked.connect(triggerPresetLocation);
}

void MainWindow::triggerPresetLocation(QModelIndex id){
    std::cout<<"trigger a location:"<<id.row()<<std::endl;
    handle->GimbalPresetLocationTigger(id.row());
    return ;
}

void MainWindow::showPresetLocation(){
    std::cout<<"show preset location:"<<std::endl;
    if (handle == nullptr){
        std::cout<< "camera ctl handle is null"<<std::endl;
    }
    std::vector<GimbalPresetLocation> locations = handle->GimbalPresetLocationGet();

    for (unsigned long long i  = 0; i < locations.size(); i++){
        std::cout <<"roll:" << locations[i].roll <<" pitch:"<<locations[i].pitch <<" yaw:"<<locations[i].yaw<<std::endl;
        std::string presetLocationItem = std::to_string(locations[i].id) + ".ratio:" + std::to_string(locations[i].zoom) + " " +
                                         "roll:" + std::to_string( locations[i].roll) + " " +
                                         "pitch:" + std::to_string(locations[i].pitch) + " " +
                                         "yaw:" + std::to_string(locations[i].yaw) + " ";

        std::cout<<"presetLocationgItem:" << presetLocationItem<<std::endl;
        QString presetLocationStr = QString::fromStdString(presetLocationItem);
        if(locations[i].id == 1){
            ui->presetInfo1->setText(presetLocationStr);
        } else if (locations[i].id == 2){
            ui->presetInfo2->setText(presetLocationStr);
        } else if (locations[i].id == 3){
            ui->presetInfo3->setText(presetLocationStr);
        } else if (locations[i].id == 4) {
            ui->presetInfo4->setText(presetLocationStr);
        }

    }
}

void MainWindow::on_gimbalResetButton_clicked()
{
    handle->GimbalLocationReset();
}

void MainWindow::on_gimbalUpButton_clicked()
{
    handle->CameraDirectionSet(0, -3);
}

void MainWindow::on_gimbalLeftButton_clicked()
{
    handle->CameraDirectionSet(5, 0);
}

void MainWindow::on_gimbalDownButton_clicked()
{
    handle->CameraDirectionSet(0, 3);
}

void MainWindow::on_gimbalRightButton_clicked()
{
    handle->CameraDirectionSet(-5, 0);
}
/*
void MainWindow::on_zoomAddButton_clicked()
{
    handle->CameraZoomSet(500);
}

void MainWindow::on_zoomReduceButton_clicked()
{
    handle->CameraZoomSet(-500);
}
*/
void MainWindow::on_autoTrackingButton_clicked()
{
    bool trackingStatus = handle->AITrackingGet();
    if (!trackingStatus){
        ui->autoTrackingButton->setIcon(QIcon(":/image/icon/on2.png"));
        ui->autoTrackingButton->setText("打开");
        ui->pushButton->setEnabled(true);
        std::cout<<"auto tracking is  on "<<std::endl;
    } else {
        ui->autoTrackingButton->setIcon(QIcon(":/image/icon/off2.png"));
        ui->autoTrackingButton->setText("关闭");
        ui->pushButton->setEnabled(false);
        std::cout<<"auto tracking is  off "<<std::endl;
    }
    handle->AITrackingSet(!trackingStatus);
}

void MainWindow::on_handPoseButton_clicked()
{
    bool handPoseStatus = !handle->AIHandposeGet();
    if (handPoseStatus){
        ui->handPoseButton->setIcon(QIcon(":/image/icon/on2.png"));
        ui->handPoseButton->setText("打开");
        std::cout<<"hand pose is  on "<<std::endl;

    } else {
        ui->handPoseButton->setIcon(QIcon(":/image/icon/off2.png"));
        ui->handPoseButton->setText("关闭");
        std::cout<<"hande pose is  off "<<std::endl;

    }
    handle->AIHandposeSet(handPoseStatus);
}

void MainWindow::on_autoZoomButton_clicked()
{
    bool currentZoomStatus = handle->CameraAutoZoomGet();
    if (!currentZoomStatus){
        //auto zoom status disable  handzoom
        ui->zoomSlider->setDisabled(true);
        ui->autoZoomButton->setText("打开");
        ui->autoZoomButton->setIcon(QIcon(":/image/icon/on2.png"));

        std::cout<<"auto zoom is  on "<<std::endl;

    } else {
        //enable hand zoom
        ui->zoomSlider->setDisabled(false);
        std::cout<<"auto zoom is  off "<<std::endl;
        ui->autoZoomButton->setText("关闭");
        ui->autoZoomButton->setIcon(QIcon(":/image/icon/off2.png"));
    }
    handle->CameraAutoZoomSet(!currentZoomStatus);
}

void MainWindow::on_uvcButton_clicked(){
    bool uvc_mode = handle->CameraUVCModeGet();

    if (!uvc_mode){
        ui->uvcButton->setIcon(QIcon(":/image/icon/off2.png"));
        ui->uvcButton->setText("关闭");
    }else {
        ui->uvcButton->setIcon(QIcon(":/image/icon/on2.png"));
        ui->uvcButton->setText("打开");
    }
    handle->CameraUVCModeCtl(!uvc_mode);
}

void MainWindow::on_objectDefaultViewButton_clicked(){
    bool currentDefaultView = handle->AIDefaultViewGet();
    if (!currentDefaultView){
        //default view landscape
        ui->objectDefaultViewButton->setText("横屏");
        std::cout<<"default view  is  landscape "<<std::endl;

    } else {
        std::cout<<"default view is not landscape "<<std::endl;
        ui->objectDefaultViewButton->setText("竖屏");
    }
    handle->AIDefaultViewSet(!currentDefaultView);
}

void MainWindow::on_witheBalanceComboBox_currentIndexChanged(const QString &arg1){
    std::cout<< "current white balance 0 : "<< ui->witheBalanceComboBox->currentText().toStdString()<<std::endl;
    QString currentWhiteBalance =  Util::GBK2UTF8(ui->witheBalanceComboBox->currentText());
    std::cout<< "current white balance : "<< currentWhiteBalance.toStdString()<<std::endl;
    ui->witheBalanceComboBox->setCurrentText(ui->witheBalanceComboBox->currentText());


}

void MainWindow::on_exposeComboBox_currentIndexChanged(const QString &arg1){
    std::cout<< "current expose  0 : "<< ui->exposeComboBox->currentText().toStdString()<<std::endl;
    std::string currentExpose = Util::GBK2UTF8(ui->exposeComboBox->currentText()).toStdString();
    std::cout<< "current expose  : "<<currentExpose<<std::endl;

    if (currentExpose == "S"){   //
        ui->isoComboBox->setDisabled(true);
        ui->exposeComboBox->setCurrentText("S");
       // handle->CameraExposeSet(ExposureMode::S);

    } else if (currentExpose == "M"){
        ui->isoComboBox->setDisabled(false);
        ui->exposeComboBox->setCurrentText("M");
        ///handle->CameraExposeSet(ExposureMode::M);

    } else {
        //auto
        ui->isoComboBox->setDisabled(true);
        ui->exposeComboBox->setCurrentText("P");
     //   handle->CameraExposeSet(ExposureMode::P);
    }
}

void MainWindow::on_isoComboBox_currentIndexChanged(const QString &arg1){
    int value = std::atoi(ui->isoComboBox->currentText().toStdString().c_str());
    //std::cout<< "current iso  0 : "<< ISOValue[value]<<std::endl;
    QString currentISO =  Util::GBK2UTF8(ui->isoComboBox->currentText());
    std::cout<< "current iso  : "<<  currentISO.toStdString()<<std::endl;
    ui->isoComboBox->setCurrentText(ui->isoComboBox->currentText());
  //  handle->CameraISOSet(ISOValue[value]);
}


void MainWindow::on_pushButton_clicked(){
    handle->TargetSelect();
    std::cout<<"target select"<<std::endl;
}

void MainWindow::on_gimbalUpLeftButton_clicked(){
     handle->CameraDirectionSet(5, -3);
}

void MainWindow::on_gimbalUpRightButton_clicked(){
     handle->CameraDirectionSet(-5, -3);
}

void MainWindow::on_gimbalDownLeftButton_clicked(){
    handle->CameraDirectionSet(5, 3);
}

void MainWindow::on_gimbalDownRightButton_clicked(){
    handle->CameraDirectionSet(-5, 3);
}

void MainWindow::on_zoomSlider_sliderReleased(){
    //1000-1x   1500-1.5x   2000-2x    5000-5
    handle->CameraZoomSet(currentZoomValue*1000);

    std::cout<<"zoom slider released, set zoom "<< currentZoomValue<<std::endl;
}

void MainWindow::on_zoomSlider_sliderPressed(){
    handle->CameraZoomSet(currentZoomValue*1000);

    std::cout<<"zoom slider pressed"<<std::endl;
}

void MainWindow::on_zoomSlider_sliderMoved(int position){
    currentZoomValue = 0.5*position+1;

    std::string currentZoom = std::to_string(currentZoomValue)+"x";
    ui->zoomLabel_2->setText(QString::fromStdString(currentZoom));
    std::cout<<"zoom slider moved position "<<position<<std::endl;

}

void MainWindow::on_powerOffButton_clicked(){
    handle->CameraPoweroff();
}

void MainWindow::on_presetLocationAddButton_1_clicked()
{
    if (handle == nullptr){
        std::cout<< "camera ctl handle is null"<<std::endl;
    }
    std::shared_ptr<GimbalLocation> location = handle->CameraDirectionGet();
    std::cout<<"roll:" << location->roll <<" pitch:"<<location->pitch <<" yaw:"<<location->yaw<<std::endl;

    std::string zoom = handle->GetAbsZoom();
    std::cout<<"zoom:" << zoom<<std::endl;

    zoom = zoom.substr(0, zoom.find("x"));
    std::cout<<"zoom:" << zoom<<std::endl;

    handle->GimbalPresetLocationAdd(1, (float)atof(zoom.c_str()), location->roll, location->pitch, location->yaw);

    std::string presetLocationItem = "1.ratio:" + zoom + " " +
                                     "roll:" + std::to_string(location->roll) + " " +
                                     "pitch:" + std::to_string(location->pitch) + " " +
                                     "yaw:" + std::to_string(location->yaw) + " ";
    std::cout<<"presetLocationgItem:" << presetLocationItem<<std::endl;
    QString presetLocationStr = QString::fromStdString(presetLocationItem);

    ui->presetInfo1->setText(presetLocationStr);
}

void MainWindow::on_presetLocationAddButton_2_clicked()
{
    if (handle == nullptr){
        std::cout<< "camera ctl handle is null"<<std::endl;
    }
    std::shared_ptr<GimbalLocation> location = handle->CameraDirectionGet();
    std::cout<<"roll:" << location->roll <<" pitch:"<<location->pitch <<" yaw:"<<location->yaw<<std::endl;

    std::string zoom = handle->GetAbsZoom();
    std::cout<<"zoom:" << zoom<<std::endl;

    zoom = zoom.substr(0, zoom.find("x"));
    std::cout<<"zoom:" << zoom<<std::endl;

    handle->GimbalPresetLocationAdd(2, (float)atof(zoom.c_str()), location->roll, location->pitch, location->yaw);

    std::string presetLocationItem = "2.ratio:" + zoom + " " +
                                     "roll:" + std::to_string(location->roll) + " " +
                                     "pitch:" + std::to_string(location->pitch) + " " +
                                     "yaw:" + std::to_string(location->yaw) + " ";
    std::cout<<"presetLocationgItem:" << presetLocationItem<<std::endl;
    QString presetLocationStr = QString::fromStdString(presetLocationItem);

    ui->presetInfo2->setText(presetLocationStr);
}

void MainWindow::on_presetLocationAddButton_3_clicked()
{
    if (handle == nullptr){
        std::cout<< "camera ctl handle is null"<<std::endl;
    }
    std::shared_ptr<GimbalLocation> location = handle->CameraDirectionGet();
    std::cout<<"roll:" << location->roll <<" pitch:"<<location->pitch <<" yaw:"<<location->yaw<<std::endl;

    std::string zoom = handle->GetAbsZoom();
    std::cout<<"zoom:" << zoom<<std::endl;

    zoom = zoom.substr(0, zoom.find("x"));
    std::cout<<"zoom:" << zoom<<std::endl;

    handle->GimbalPresetLocationAdd(3, (float)atof(zoom.c_str()), location->roll, location->pitch, location->yaw);

    std::string presetLocationItem = "3.ratio:" + zoom + " " +
                                     "roll:" + std::to_string(location->roll) + " " +
                                     "pitch:" + std::to_string(location->pitch) + " " +
                                     "yaw:" + std::to_string(location->yaw) + " ";
    std::cout<<"presetLocationgItem:" << presetLocationItem<<std::endl;
    QString presetLocationStr = QString::fromStdString(presetLocationItem);

    ui->presetInfo3->setText(presetLocationStr);
}

void MainWindow::on_presetLocationAddButton_4_clicked()
{
    if (handle == nullptr){
        std::cout<< "camera ctl handle is null"<<std::endl;
    }
    std::shared_ptr<GimbalLocation> location = handle->CameraDirectionGet();
    std::cout<<"roll:" << location->roll <<" pitch:"<<location->pitch <<" yaw:"<<location->yaw<<std::endl;

    std::string zoom = handle->GetAbsZoom();
    std::cout<<"zoom:" << zoom<<std::endl;

    zoom = zoom.substr(0, zoom.find("x"));
    std::cout<<"zoom:" << zoom<<std::endl;

    handle->GimbalPresetLocationAdd(4, (float)atof(zoom.c_str()), location->roll, location->pitch, location->yaw);

    std::string presetLocationItem = "4.ratio:" + zoom + " " +
                                     "roll:" + std::to_string(location->roll) + " " +
                                     "pitch:" + std::to_string(location->pitch) + " " +
                                     "yaw:" + std::to_string(location->yaw) + " ";
    std::cout<<"presetLocationgItem:" << presetLocationItem<<std::endl;
    QString presetLocationStr = QString::fromStdString(presetLocationItem);

    ui->presetInfo4->setText(presetLocationStr);
}

void MainWindow::on_preesetLocationEnable_1_clicked()
{
    handle->GimbalPresetLocationTigger(1);

}

void MainWindow::on_preesetLocationEnable_2_clicked()
{
    handle->GimbalPresetLocationTigger(2);
}

void MainWindow::on_preesetLocationEnable_3_clicked()
{
    handle->GimbalPresetLocationTigger(3);
}

void MainWindow::on_preesetLocationEnable_4_clicked()
{
    handle->GimbalPresetLocationTigger(4);
}

void MainWindow::on_presetLocationDel_1_clicked()
{
    handle->GimbalPresetLocationRemove(1);
    ui->presetInfo1->setText("");
    ui->presetName1->setText("");
}

void MainWindow::on_presetLocationDel_2_clicked()
{
    handle->GimbalPresetLocationRemove(2);
    ui->presetInfo2->setText("");
    ui->presetName2->setText("");
}

void MainWindow::on_preesetLocationDel_3_clicked()
{
    handle->GimbalPresetLocationRemove(3);
    ui->presetInfo3->setText("");
    ui->presetName3->setText("");
}

void MainWindow::on_preesetLocationDel_4_clicked()
{
    handle->GimbalPresetLocationRemove(4);
    ui->presetInfo4->setText("");
    ui->presetName4->setText("");

}
