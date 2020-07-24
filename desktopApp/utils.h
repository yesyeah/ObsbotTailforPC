#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <iostream>
#include <qstring.h>
#include <qtextcodec.h>

#define CAMERA_CTL_PORT 80
#define AI_CTL_PORT 27739

enum CommandId{
    WIFI_CFG =  510,
    WIFI_MSG = 511,
    RECORD_START = 622,
    RECORD_STOP = 623,
    ZOOM_TRIGGER = 701,
    RTMP_CFG = 711,
    RTMP_MSG = 710,
    ZOOM_CFG = 802,
    ZOOM_GET = 803,
};

enum WifiMode{
    WIFI_STATION = 0,
    WIFI_AP = 1,
};

enum SpeedMode{
    SPD_LAZY = 0,
    SPD_SLOW = 1,
    SPD_NORMAL = 2,
    SPD_FAST = 3,
    SPD_CRAZY = 4,
};

enum AICfgKey{
    AI_CFG_ENABLE = 0,
    AI_CFG_HANDPOSE = 2,
    AI_CFG_GIMBAL_LOCK = 3,
    AI_CFG_DEFAULT_VIEW = 4,
    AI_CFG_AUTOZOOM = 5,
    AI_CFG_TARGET_TYPE = 6,
};

enum CameraViewMode{
    VIEW_HORIZONTAL = 0,
    VIEW_VERTICAL =1,
};

enum GimbalLockStatus{
    UNLOCK = 0,
    LOCK = 1,
};

enum HandPoseStatus{
    HP_OFF = 0,
    HP_ON = 1,
};

enum DefaultView{
    LANDSCAPE = 0,
    PORTRIAT = 1,
};

enum AutoZoom{
    AZ_OFF = 0,
    AZ_ON = 1,
};

class Util{
public:

    static void InvertUint8(unsigned char *dBuf,unsigned char *srcBuf);
    static void InvertUint16(unsigned short *dBuf,unsigned short *srcBuf);
    static void InvertUint32(unsigned int *dBuf,unsigned int *srcBuf);
    static unsigned short CRC16_USB( char *data, unsigned int datalen);

    static std::string string_To_UTF8(const std::string & str);
    static QString GBK2UTF8(const QString &str);

    static QString UTF82GBK(const QString &str);

    static std::string GBK2UTF8(std::string &str);

    static std::string UTF82GBK(std::string &str);
};



#endif
