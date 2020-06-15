#include "cameracontrol.h"
#include <sstream>

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    std::string data((const char*) ptr, (size_t) size * nmemb);
    *((stringstream*) stream) << data << std::endl;
    return size * nmemb;
}


CameraControl::CameraControl(){
    curl_global_init(CURL_GLOBAL_ALL);
}

void CameraControl::init(){
    //cameraIP = GetCameraIP();
    cameraIP = "192.168.0.105";
    presetLocationId = 0;

    cameraConctrlAddr = "http://"+cameraIP+":80";
    aiConctrlAddr = "http://"+cameraIP+":27739";
    currentZoomSpeed = "100";
    wifiSSID = "";
    wifiPassword = "";

    aiInit();
    cameraInit();
    return;
}

bool CameraControl::aiInit(){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"ai init failed,  curl failed!";
        return false;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<< "debug ai init response : "<<response.str()<<std::endl;

    json recv_msg = json::parse(response.str());
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

    head_list = nullptr;
    return true;
}

bool CameraControl::cameraInit(){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"camera init failed,  curl failed!";
        return false;
    }

    std::cout<<"camera init start"<<std::endl;

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/camera";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);
    std::cout<<"camera init start 1"<<std::endl;

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);\
    std::cout<<"camera init start 2"<<std::endl;

    std::cout<< "debug camera init response : "<<response.str()<<std::endl;

    json recv_msg = json::parse(response.str());;
    currentZoom = recv_msg["Zoom"];

    return true;
}

bool CameraControl::paramUpdate(){
    return aiInit() && cameraInit();
}

bool CameraControl::WifiStatusGet(){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"wifi status get failed,  curl is nullptr!";
        return false;
    }

    std::string url = cameraConctrlAddr;

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["msg_id"] = CommandId::WIFI_MSG;

    std::string request_data = send_msg.dump();
    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"wifi status get result : "<<response.str()<<std::endl;
    return true;
}

bool CameraControl::WifiStatusSet(bool is_ap_mode){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"wifi status set failed,  curl is nullptr!";
        return false;
    }

    std::string url = cameraConctrlAddr;

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["msg_id"] = CommandId::WIFI_CFG;
    if (is_ap_mode){
        send_msg["mode"] = WifiMode::WIFI_AP;
    } else {
        send_msg["mode"] = WifiMode::WIFI_STATION;
        send_msg["ssid"] = wifiSSID;
        send_msg["passwd"] = wifiPassword;
    }

    std::string request_data = send_msg.dump();
    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"wifi status set result : "<<response.str()<<std::endl;

    return true;
}

bool CameraControl::WifiInfoSet(std::string ssid, std::string pwd){
    wifiSSID = ssid;
    wifiPassword = pwd;
    return true;
}

bool CameraControl::DeviceSearch(){
    //ap mode get wifi via get connected wifi info


    //station mode get via device search

    return true;
}


std::string CameraControl::GetCameraIP(){
    //mdns scan device, then get device ip through app
    return cameraIP;
}

bool CameraControl::SetCameraIP(std::string ip_addr){
    cameraIP = ip_addr;
    return true;
}

bool CameraControl::CameraDirectionSet(int x, int y){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"ai init failed,  curl failed!";
        return false;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    std::cout<< "debug ai init response : "<<response.str()<<std::endl;

    json send_msg;
    send_msg["cmd"] = "setRelDegree";
    send_msg["rollDegree"] = -10000;
    send_msg["pitchDegree"] = y;
    send_msg["yawDegree"] = x;

    std::string request_data = send_msg.dump();
    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, request_data.c_str());
    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"camera direction set result : "<<response.str()<<std::endl;

    return true;

}

std::shared_ptr<GimbalLocation> CameraControl::CameraDirectionGet(){
    std::shared_ptr<GimbalLocation> location = std::make_shared<GimbalLocation>();

    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"ai init failed,  curl failed!";
        return location;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"camera direction get result : "<<response.str()<<std::endl;
    json recv_msg = json::parse(response.str());
    currentRoll = recv_msg["Degree"][0];
    currentYaw = recv_msg["Degree"][1];
    currentPitch = recv_msg["Degree"][2];

    location->roll = currentRoll;
    location->pitch = currentPitch;
    location->yaw = currentYaw;
    return location;
}

bool CameraControl::GimbalLocationReset(){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"gimbal reset failed,  curl is nullptr!";
        return false;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["cmd"] = "reset";

    std::string request_data = send_msg.dump();
    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"gimbal reset  result : "<<response.str()<<std::endl;

    return true;
}


bool CameraControl::GimbalLock(bool is_lock){
    //post msg via http
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"gimbal lock failed,  curl is nullptr!";
        return false;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["cmd"] = "lock";
    if (is_lock){
        send_msg["mode"] = GimbalLockStatus::LOCK;
    } else {
        send_msg["mode"] = GimbalLockStatus::UNLOCK;
    }

    std::string request_data = send_msg.dump();

    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());
    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"camera lock set result : "<<response.str()<<std::endl;

    return true;
}

std::vector<GimbalPresetLocation> CameraControl::GimbalPresetLocationGet(){
    std::vector<GimbalPresetLocation> locations;
    locations.clear();
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"gimbal preset location get  failed,  curl failed!";
        return locations;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");


    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["cmd"] = "presetQuery";

    std::string request_data = send_msg.dump();

    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    json recv_msg = json::parse(response.str());;

    std::cout<<"gimbal preset location get result : "<<response.str()<<std::endl;


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
    curlHandle = curl_easy_init();
    std::cout<<"zoom:" << zoom <<"   roll:" << roll <<" pitch:"<<pitch <<" yaw:"<<yaw<<std::endl;


    if (curlHandle == nullptr){
        std::cout<<"gimbal preset location add  failed,  curl failed!";
        return -1;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");


    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["cmd"] = "presetAdd";
    send_msg["id"] = presetLocationId;
    send_msg["roll"] = roll;
    send_msg["pitch"] = pitch;
    send_msg["pan"] = yaw;
    send_msg["ratio"] = zoom;

    std::string request_data = send_msg.dump();
    std::cout<<"gimbal preset location add  : "<<request_data<<std::endl;

    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);


    std::cout<<"gimbal preset location add result : "<<response.str()<<std::endl;
    presetLocationId = presetLocationId + 1;

    return presetLocationId;
}

bool CameraControl::GimbalPresetLocationRemove(int id){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"gimbal preset location remove  failed,  curl failed!";
        return false;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");


    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["cmd"] = "presetRemove";
    send_msg["id"] = id;

    std::string request_data = send_msg.dump();

    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);


    std::cout<<"gimbal preset location remove result : "<<response.str()<<std::endl;
    return true;
}

bool CameraControl::GimbalPresetLocationTigger(int id){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"gimbal preset location trigger  failed,  curl failed!";
        return false;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai/gimbal";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");


    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["cmd"] = "presetTrigger";
    send_msg["id"] = id;

    std::string request_data = send_msg.dump();

    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"gimbal preset location trigger result : "<<response.str()<<std::endl;
    return true;
}

bool CameraControl::AIHandposeSet(bool onoff){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"hand pose set failed,  curl failed!";
        return false;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");


    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);


    json send_msg;
    send_msg["cmd"] = "SdkSetConfig";
    send_msg["key"] = AICfgKey::AI_CFG_HANDPOSE;
    if (onoff){
        send_msg["val"] = HandPoseStatus::HP_ON;
    }else{
        send_msg["val"] = HandPoseStatus::HP_OFF;
    }

    std::string request_data = send_msg.dump();

    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"hand pose set result : "<<response.str()<<std::endl;

    return true;
}

bool CameraControl::AIHandposeGet(){
    return isHandposeCtl;
}

bool CameraControl::AITrackingSet(bool is_tracking){
    return GimbalLock(!is_tracking);
}

bool CameraControl::AITrackingGet(){
    return isTracking;
}

bool CameraControl::AIDefaultViewSet(bool is_landscape){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"ai default view set failed,  curl failed!";
        return false;
    }
    std::string url = aiConctrlAddr + "/obsbot/tail/ai";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");


    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["cmd"] = "SdkSetConfig";
    send_msg["key"] = AICfgKey::AI_CFG_DEFAULT_VIEW;
    if (is_landscape){
        send_msg["val"] = DefaultView::LANDSCAPE;
    }else{
        send_msg["val"] = DefaultView::PORTRIAT;
    }

    std::string request_data = send_msg.dump();

    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"ai default view  set result : "<<response.str()<<std::endl;

    return true;
}

bool CameraControl::AIDefaultViewGet(){
    return isDefaultLandscape;
}

bool CameraControl::CameraZoomSet(int pos, int speed){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"camera zoom set failed,  curl failed!";
        return false;
    }

    std::string url  = cameraConctrlAddr;

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");


    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["msg_id"] = CommandId::ZOOM_CFG;
    send_msg["pos"] = pos;
    send_msg["speed"] = speed;

    std::string request_data = send_msg.dump();

    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"camera zoom  set result : "<<response.str()<<std::endl;

    return true;
}

std::string  CameraControl::CameraZoomGet(){
    return currentZoom;
}

bool CameraControl::CameraZoomTigger(){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"camera zoom trigger failed,  curl failed!";
        return false;
    }

    std::string url  = cameraConctrlAddr;

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");


    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);

    json send_msg;
    send_msg["msg_id"] = CommandId::ZOOM_TRIGGER;
    send_msg["x"] = 50;
    send_msg["y"] = 50;

    std::string request_data = send_msg.dump();

    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"camera zoom trigger result : "<<response.str()<<std::endl;
    return true;
}

bool CameraControl::CameraAutoZoomSet(bool on){
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"camera auto zoom set failed,  curl failed!";
        return false;
    }

    std::string url = aiConctrlAddr + "/obsbot/tail/ai";

    std::stringstream response;
    curl_slist* head_list = nullptr;
    curl_slist_append(head_list, "Content-Type:application/json");


    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &response);


    json send_msg;
    send_msg["cmd"] = "SdkSetConfig";
    send_msg["key"] = AICfgKey::AI_CFG_AUTOZOOM;
    if (on){
        send_msg["val"] = AutoZoom::AZ_ON;
    }else{
        send_msg["val"] = AutoZoom::AZ_OFF;
    }

    std::string request_data = send_msg.dump();

    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,request_data.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    std::cout<<"camera auto zoom  set result : "<<response.str()<<std::endl;

    return true;
}

bool CameraControl::CameraAutoZoomGet(){
    return isAutoZoom;
}
