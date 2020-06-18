#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "curl/curl.h"
#include "curl/easy.h"
#include "utils.h"
#include "icmp_ping.h"
#include "httpservice.h"

#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

#define CAMERA_CONTROL_PORT 80
#define AI_CONTROL_PORT 27739

class GimbalLocation{
public:
    float roll;
    float pitch; //y
    float yaw;  //x
};

class GimbalPresetLocation{
public:
    float zoom;
    float roll;
    float pitch;
    float yaw;
    int id;
};

class ZoomStatus{
public:
    float zoomRatio;
    float zoomSpeed;

};

class CameraControl
{
public:
    CameraControl();
    ~CameraControl(){
        curlHandle = nullptr;
    }

    void init();
    bool aiInit();
    bool cameraInit();
    bool paramUpdate();

    bool WifiStatusGet();
    bool WifiStatusSet(bool is_ap_mode);
    bool WifiInfoSet(std::string ssid, std::string pwd);

    std::vector<std::string> DeviceSearch();

    bool CameraDirectionSet(int x, int y);  // 镜头方向控制
    std::shared_ptr<GimbalLocation> CameraDirectionGet();
    bool GimbalLocationReset();                                              //云台复位
    bool GimbalLock(bool is_lock);                                              //云台锁定开关

    std::vector<GimbalPresetLocation> GimbalPresetLocationGet();   // 预置位设置
    int GimbalPresetLocationAdd(float zoom, float roll, float pitch, float yaw);
    bool GimbalPresetLocationRemove(int id);
    bool GimbalPresetLocationTigger(int id);

    bool AIHandposeSet(bool onoff);     //手势控制开关
    bool AIHandposeGet();
    bool AITrackingSet(bool is_tracking);     //自动跟踪开关。选人跟踪开关
    bool AITrackingGet();
    bool AIDefaultViewSet(bool is_landscape);  //横竖屏切换
    bool AIDefaultViewGet();

    bool CameraAutoZoomSet(bool on);
    bool CameraAutoZoomGet();
    bool CameraZoomSet(int pos, int speed);                                     //调焦，变焦（自动 手动）
    std::string CameraZoomGet();
    bool CameraZoomTigger();
    bool SetCameraIP(std::string ip_addr);
    std::string GetCameraIP();
    std::string GetCameraDefaultIP();


private:
    std::string GetCameraUrl();
    std::string GetAIUrl();
    bool GetLocalIP();
    bool isStatMode(std::string ip);

    CURL* curlHandle;
    HttpService httpHandle;
    std::string localIP;
    std::string cameraIP;
    std::string cameraDefaultIP;
    std::string curlHead;

    std::string cameraConctrlAddr;
    std::string aiConctrlAddr;

    int isGimbalLock;
    GimbalLocation gimbalCurrentLocation;
    GimbalLocation gimbalDefaultResetLocation;
    GimbalPresetLocation gimbalPreserLocation;
    std::vector<GimbalPresetLocation> gimbalPresetLocationList;

    int isAutoTracking;
    int isTargetTracking;

    int isAIOn;
    int isTracking;
    int isHandposeCtl;
    SpeedMode speedMode;
    float currentRoll;
    float currentPitch;
    float currentYaw;
    int isAIReady;
    int isDefaultLandscape;
    int isAutoZoom;
    int targetType;
    std::string currentZoom;
    std::string currentZoomSpeed;
    std::string versionNum;

    int presetLocationId;

    std::string wifiSSID;
    std::string wifiPassword;
    std::shared_ptr<CPing> pingHandle;

};

#endif // CAMERACONTROL_H
