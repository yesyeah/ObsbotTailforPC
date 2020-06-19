#include "cameracontrol.h"
#include "icmp_ping.h"
#include <sstream>
#include <WinSock2.h>
#include <Wininet.h>
#include <windows.h>
#include <QApplication>
#include <QTextCodec>
#include <QProcess>
#include <iphlpapi.h>
#include <Sensapi.h>
#include <iostream>
using namespace std;
extern size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);/* {
    std::string data((const char*) ptr, (size_t) size * nmemb);
    *((stringstream*) stream) << data << std::endl;
    return size * nmemb;
}*/

CameraControl::CameraControl(){
    curl_global_init(CURL_GLOBAL_ALL);
    //cameraIP = GetCameraIP();
    GetLocalIP();

    cameraIP = "";
    cameraDefaultIP = "192.168.0.1";
    presetLocationId = 0;

    currentZoomPos = 0;
    currentZoomSpeed = 0;

    pingHandle = std::make_shared<CPing>();
    wifiSSID = "";
    wifiPassword = "";
}

bool CameraControl::GetLocalIP(){
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);

    int IPnumPerNetCard = 0;
    delete pIpAdapterInfo;
    pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
    nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);

    while (pIpAdapterInfo){
        cout << "name:" << pIpAdapterInfo->AdapterName << endl;
        cout << "description:" << pIpAdapterInfo->Description << endl;
        cout << "type:";
        switch (pIpAdapterInfo->Type){
            case MIB_IF_TYPE_OTHER:
                cout << "OTHER" << endl;
                break;
            case MIB_IF_TYPE_ETHERNET:
                cout << "ETHERNET" << endl;
                break;
            case MIB_IF_TYPE_TOKENRING:
                cout << "TOKENRING" << endl;
                break;
            case MIB_IF_TYPE_FDDI:
                cout << "FDDI" << endl;
                break;
            case MIB_IF_TYPE_PPP:
                cout << "PPP" << endl;
                break;
            case MIB_IF_TYPE_LOOPBACK:
                cout << "LOOPBACK" << endl;
                break;
            case MIB_IF_TYPE_SLIP:
                cout << "SLIP" << endl;
                break;
            default:
                cout << "" << endl;
                break;
        }
        for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++){
            if (i < pIpAdapterInfo->AddressLength - 1){
                printf("%02X-", pIpAdapterInfo->Address[i]);
            }else{
                printf("%02X\n", pIpAdapterInfo->Address[i]);
            }
            IPnumPerNetCard = 0;
            IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);
            do{
                localIP = pIpAddrString->IpAddress.String;
                if (std::strcmp(localIP.c_str(), "0.0.0.0") != 0){
                    cout << "IP:" << pIpAddrString->IpAddress.String << endl;
                    cout << "netmask:" << pIpAddrString->IpMask.String << endl;
                    cout << "gateway:" << pIpAdapterInfo->GatewayList.IpAddress.String << endl;

                    std::cout<<"local ip "<< " is "<<localIP<<std::endl;
                    return true;
                }
                pIpAddrString = pIpAddrString->Next;
            } while (pIpAddrString);

            pIpAdapterInfo = pIpAdapterInfo->Next;
            cout << "\n" << endl;
        }
    }
    if (pIpAdapterInfo){
        delete pIpAdapterInfo;
    }
    return false;
}

void CameraControl::init(){
    cameraConctrlAddr = "http://"+cameraIP+":80";
    aiConctrlAddr = "http://"+cameraIP+":27739";
    aiInit();
    cameraInit();
    //WifiInfoGet(cameraIP);
    return;
}

bool CameraControl::aiInit(){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai";
    std::string req;
    std::string res;
    httpHandle.getRequest(url, req, res);

    if (res != ""){
        json recv_msg = json::parse(res);
        if (recv_msg["aisdk"] == 1){
            std::cout<<"AI is on"<<std::endl;

            isAIOn = recv_msg["aisdk"];
            std::cout<<"ai status:" <<isAIOn<<std::endl;

            isTracking = recv_msg["tracking"];
            std::cout<<"tracking status:" <<isTracking<<std::endl;

            // isGimbalLock = !recv_msg["tracking"];
            // std::cout<<"gimbal status:" <<isGimbalLock<<std::endl;

            isHandposeCtl = recv_msg["handpose"];
            std::cout<<"hand pose ctl status:" <<isHandposeCtl<<std::endl;

            speedMode = recv_msg["speedMode"];
            std::cout<<"speedmode status:" <<speedMode<<std::endl;

            isAIReady = recv_msg["ready"];
            std::cout<<"ai ready status:" <<isAIReady<<std::endl;

            isDefaultLandscape = recv_msg["defaultView"];
            std::cout<<"default view status:" <<isDefaultLandscape<<std::endl;

            isAutoZoom = recv_msg["autoZoom"];
            std::cout<<"auto zoom status:" <<isAutoZoom<<std::endl;

            targetType = recv_msg["targetType"];
            std::cout<<"target type status:" <<targetType<<std::endl;

        } else {
            std::cout<<"AI is off"<<std::endl;
        }
    }

    return true;
}

bool CameraControl::cameraInit(){
    CameraZoomGet();
    return true;
}

bool CameraControl::paramUpdate(){
    return aiInit() && cameraInit();
}

bool CameraControl::WifiStatusGet(){
    std::string url = cameraConctrlAddr;
    std::string res;
    json send_msg;
    send_msg["msg_id"] = CommandId::WIFI_MSG;
    httpHandle.postRequest(url, send_msg.dump(), res);

    json response_msg = json::parse(res);
    if (response_msg["mode"] == 0){
        std::cout<<"get wifi ssid:"<<response_msg["ssid"]<<std::endl;
        std::cout<<"get wifi mac:"<<response_msg["mac_addr"]<<std::endl;
    }else {
        std::cout<<"current wifi is ap mode ."<<std::endl;
    }

    std::cout<<"wifi status get result : "<<res<<std::endl;
    return true;
}

bool CameraControl::WifiStatusSet(bool is_ap_mode){
    std::string url = cameraConctrlAddr;
    std::string res;
    json send_msg;
    send_msg["msg_id"] = CommandId::WIFI_CFG;
    if (is_ap_mode){
        send_msg["mode"] = WifiMode::WIFI_AP;
    } else {
        send_msg["mode"] = WifiMode::WIFI_STATION;
        send_msg["ssid"] = wifiSSID;
        send_msg["passwd"] = wifiPassword;
    }

    httpHandle.postRequest(url, send_msg.dump(), res);
    std::cout<<"wifi status set result : "<<res<<std::endl;

    return true;
}

bool CameraControl::WifiInfoSet(std::string ssid, std::string pwd){
    wifiSSID = ssid;
    wifiPassword = pwd;
    return true;
}

bool CameraControl::isStatMode(std::string ip){
    std::string url = "http://"+ip+":80";
    std::string res;

    json send_msg;
    send_msg["msg_id"] = CommandId::WIFI_MSG;
    httpHandle.postRequest(url, send_msg.dump(), res);

    if (res != ""){
        json response_msg = json::parse(res);
        if (response_msg["mode"] == 0){
            //std::cout<<"get wifi ssid:"<<response_msg["ssid"]<<std::endl;
           // std::cout<<"get wifi mac:"<<response_msg["mac_addr"]<<std::endl;
            return true;
        }
    }
    return false;
}

std::vector<std::string> CameraControl::DeviceSearch(){
    PingReply reply;
    std::string testIP;
    std::string preIP = localIP.substr(0, localIP.rfind(".")+1);
    double time_start = GetTickCount();
    std::vector<std::string> addr_list;
    addr_list.clear();

    for (int i = 0; i < 127; i++){
        testIP = preIP + std::to_string(128-i);
        if (pingHandle->Ping(testIP.c_str(), &reply, 40)){
            if (isStatMode(testIP)){
                addr_list.insert(addr_list.begin(), testIP);
                std::cout<<testIP<<" is on"<<std::endl;
            }
        }
        testIP = preIP + std::to_string(128+i);
        if (pingHandle->Ping(testIP.c_str(), &reply, 40)){
            if (isStatMode(testIP)){
                addr_list.insert(addr_list.begin(), testIP);
                std::cout<<testIP<<" is on"<<std::endl;
            }
        }
    }
    double  time_end = GetTickCount();
    std::cout<<"search device used  "<< time_end-time_start <<" ms"<<std::endl;

    return addr_list;
}


std::string CameraControl::GetCameraIP(){
    return cameraIP;
}

std::string CameraControl::GetCameraDefaultIP(){
    return cameraDefaultIP;
}

bool CameraControl::SetCameraIP(std::string ip_addr){
    cameraIP = ip_addr;
    return true;
}

bool CameraControl::CameraDirectionSet(int x, int y){
    CameraDirectionGet();

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";
    std::string res;
    json send_msg;

    int pitch = y + currentPitch;
    int yaw = x + currentYaw;
    std::cout<<"set yaw "<<yaw << " set pitch "<<pitch <<std::endl;

    send_msg["cmd"] = "setAbsDegree";
    send_msg["rollDegree"] = -1000;
    if (y == 0){
        send_msg["pitchDegree"] = -1000;
        send_msg["yawDegree"] = yaw;
    }
    if (x == 0){
        send_msg["pitchDegree"] = pitch;
        send_msg["yawDegree"] = -1000;
    }

    httpHandle.postRequest(url, send_msg.dump(), res);
    std::cout<<"camera direction set result : "<<res<<std::endl;

    return true;
}

std::shared_ptr<GimbalLocation> CameraControl::CameraDirectionGet(){
    std::shared_ptr<GimbalLocation> location = std::make_shared<GimbalLocation>();

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";

    std::string req;
    std::string res;

    httpHandle.getRequest(url, req, res);
    std::cout<<"camera direction get result : "<<res<<std::endl;
    json recv_msg = json::parse(res);
    currentRoll = recv_msg["Degree"][0];
    currentPitch = recv_msg["Degree"][1];
    currentYaw = recv_msg["Degree"][2];
    std::cout<<"get yaw "<<currentYaw << " get pitch "<<currentPitch <<std::endl;
    location->roll = currentRoll;
    location->pitch = currentPitch;
    location->yaw = currentYaw;
    return location;
}

bool CameraControl::GimbalLocationReset(){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";
    std::string res;
    json send_msg;
    send_msg["cmd"] = "reset";
    httpHandle.postRequest(url, send_msg.dump(), res);

    std::cout<<"gimbal reset  result : "<<res<<std::endl;

    return true;
}


bool CameraControl::GimbalLock(bool is_lock){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";
    std::string res;

    json send_msg;
    send_msg["cmd"] = "lock";
    if (is_lock){
        send_msg["mode"] = GimbalLockStatus::LOCK;
    } else {
        send_msg["mode"] = GimbalLockStatus::UNLOCK;
    }

    httpHandle.postRequest(url, send_msg.dump(), res);
    isTracking = !is_lock;
    std::cout<<"camera lock set result : "<<res<<std::endl;
    return true;
}

bool CameraControl::GetGimbalLockStatus(){
    return isTracking;
}

std::vector<GimbalPresetLocation> CameraControl::GimbalPresetLocationGet(){
    std::vector<GimbalPresetLocation> locations;
    locations.clear();

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";
    std::string res;
    json send_msg;
    send_msg["cmd"] = "presetQuery";

    httpHandle.postRequest(url, send_msg.dump(), res);

    json recv_msg = json::parse(res);;
    std::cout<<"gimbal preset location get result : "<<res<<std::endl;

    for(unsigned int i = 0; i < recv_msg.size(); i++){
        GimbalPresetLocation location;
        location.zoom = recv_msg[i]["ratio"];
        location.id = recv_msg[i]["id"];
        location.roll = recv_msg[i]["roll"];
        location.yaw = recv_msg[i]["pan"];

        location.pitch = recv_msg[i]["pitch"];
        locations.insert(locations.begin()+i, location);
    }

    return locations;
}

int CameraControl::GimbalPresetLocationAdd(float zoom, float roll, float pitch, float yaw){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";
    std::string res;

    json send_msg;
    send_msg["cmd"] = "presetAdd";
    send_msg["id"] = presetLocationId;
    send_msg["roll"] = roll;
    send_msg["pitch"] = pitch;
    send_msg["pan"] = yaw;
    send_msg["ratio"] = zoom;

    httpHandle.postRequest(url, send_msg.dump(), res);
    std::cout<<"gimbal preset location add result : "<<res<<std::endl;
    presetLocationId = presetLocationId + 1;

    return presetLocationId;
}

bool CameraControl::GimbalPresetLocationRemove(int id){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";
    std::string res;
    json send_msg;
    send_msg["cmd"] = "presetRemove";
    send_msg["id"] = id;
    httpHandle.postRequest(url, send_msg.dump(), res);

    std::cout<<"gimbal preset location remove result : "<<res<<std::endl;
    return true;
}

bool CameraControl::GimbalPresetLocationTigger(int id){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";
    std::string res;
    json send_msg;
    send_msg["cmd"] = "presetTrigger";
    send_msg["id"] = id;
    httpHandle.postRequest(url, send_msg.dump(), res);

    std::cout<<"gimbal preset location trigger result : "<<res<<std::endl;
    return true;
}

bool CameraControl::AIHandposeSet(bool onoff){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai";
    std::string res;

    json send_msg;
    send_msg["cmd"] = "SdkSetConfig";
    send_msg["key"] = AICfgKey::AI_CFG_HANDPOSE;
    if (onoff){
        send_msg["val"] = HandPoseStatus::HP_ON;
    }else{
        send_msg["val"] = HandPoseStatus::HP_OFF;
    }
    httpHandle.postRequest(url, send_msg.dump(), res);

    isHandposeCtl = onoff;

    std::cout<<"hand pose set result : "<<res<<std::endl;
    paramUpdate();

    return true;
}

bool CameraControl::AIHandposeGet(){
    paramUpdate();
    return isHandposeCtl;
}

bool CameraControl::AITrackingSet(bool is_tracking){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai";
    std::string res;

    json send_msg;
    send_msg["cmd"] = "SdkSetConfig";
    send_msg["key"] = AICfgKey::AI_CFG_GIMBAL_LOCK;
    if (isTracking){
        send_msg["val"] = 1;
    } else {
        send_msg["val"] = 0;
    }
    httpHandle.postRequest(url, send_msg.dump(), res);

    paramUpdate();
    return true;
}

bool CameraControl::AITrackingGet(){
    paramUpdate();
    return isTracking;
}

bool CameraControl::AIDefaultViewSet(bool is_landscape){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai";
    std::string res;
    json send_msg;
    send_msg["cmd"] = "SdkSetConfig";
    send_msg["key"] = AICfgKey::AI_CFG_DEFAULT_VIEW;
    if (is_landscape){
        send_msg["val"] = DefaultView::LANDSCAPE;
    }else{
        send_msg["val"] = DefaultView::PORTRIAT;
    }

    httpHandle.postRequest(url, send_msg.dump(), res);
    std::cout<<"ai default view  set result : "<<res<<std::endl;

    return true;
}

bool CameraControl::AIDefaultViewGet(){
    return isDefaultLandscape;
}

bool CameraControl::CameraZoomSet(int pos){
    CameraZoomGet();
    std::string url  = cameraConctrlAddr;
    std::string res;
    json send_msg;
    send_msg["msg_id"] = CommandId::ZOOM_CFG;
    send_msg["pos"] = currentZoomPos+pos;
    send_msg["speed"] = 5;

    httpHandle.postRequest(url, send_msg.dump(), res);
    std::cout<<"camera zoom  set result : "<<res<<std::endl;

    currentZoomPos = currentZoomPos + pos;
    return true;
}

bool  CameraControl::CameraZoomGet(){
    std::string url  = cameraConctrlAddr;
    std::string res;
    json send_msg;
    send_msg["msg_id"] = CommandId::ZOOM_GET;

    httpHandle.postRequest(url, send_msg.dump(), res);
    if (res != ""){
        json response = json::parse(res);
        currentZoomPos = response["pos"];
        currentZoomSpeed = response["speed"];
        std::cout<<"camera zoom : "<<currentZoomPos <<" camera zoom speed :"<<currentZoomSpeed<<std::endl;
    }

    return true;
}

int CameraControl::GetCurrentZoom(){
    return currentZoomPos;
}

int CameraControl::GetCurrentZoomSpeed(){
    return currentZoomSpeed;
}

std::string CameraControl::GetAbsZoom(){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai/camera";
    std::string req;
    std::string res;
    httpHandle.getRequest(url, req, res);

    if (res != ""){
        json recv_msg = json::parse(res);
        absZoom = recv_msg["Zoom"];
    }

    return absZoom;
}

bool CameraControl::CameraZoomTigger(){
    std::string url  = cameraConctrlAddr;
    std::string res;

    json send_msg;
    send_msg["msg_id"] = CommandId::ZOOM_TRIGGER;
    send_msg["x"] = 50;
    send_msg["y"] = 50;

    httpHandle.postRequest(url, send_msg.dump(), res);

    std::cout<<"camera zoom trigger result : "<<res<<std::endl;
    return true;
}

bool CameraControl::CameraAutoZoomSet(bool on){
    std::string url = aiConctrlAddr + "/obsbot/tail/ai";
    std::string res;
    json send_msg;
    send_msg["cmd"] = "SdkSetConfig";
    send_msg["key"] = AICfgKey::AI_CFG_AUTOZOOM;
    if (on){
        send_msg["val"] = AutoZoom::AZ_ON;
    }else{
        send_msg["val"] = AutoZoom::AZ_OFF;
    }

    httpHandle.postRequest(url, send_msg.dump(), res);
    std::cout<<"camera auto zoom  set result : "<<res<<std::endl;
    isAutoZoom = on;

    return true;
}

bool CameraControl::CameraAutoZoomGet(){
    return isAutoZoom;
}
