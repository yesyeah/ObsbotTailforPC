#ifndef REMO_PROTOCOL_UTILS_H
#define REMO_PROTOCOL_UTILS_H

enum CameraCommand{
    ParamGet = 0x0,
    ParamSet = 0x1,
    ParamSupport = 0x2,
    Control = 0x3,
    Custom = 0x7
};

enum CameraDescription{
    WorkMode = 0x0,
    WhiteBalance = 0x65,       //get 0 set 1
    Exposure = 0x67,
    ExposureP = 0x68,
    ShutterS = 0x69,
    ExposureS = 0x6a,
    ApertureA = 0x6b,
    ExposureA = 0x6c,
    ApertureM = 0x6d,
    ShutterM = 0x6e,
    IsoM = 0x6f,
    ApertureCur = 0x70,           //get all mode support
    ShutterCur = 0x71,            //get all mode ...
    IsoCur = 0x72,                //get all mode ...
    ExposureCompensationCur = 0x73,
    ZoomMode = 0x77,
    Zoom = 0x7c,
};


enum AICommand{
    GimbalCtlTirgger = 0x21,
    ZoomSet = 0x47,
};

enum BatteryCommand{
    TurnOff = 0x88,

};

enum ExposureType{
    AUTO = 0,
    INCANDESCENT = 1,
    FLUORESCENT = 2,
    SUNNY =3,
    WINDY = 4,
    CUSTOM = 5,
};

typedef struct Remo_Camera_WhiteBalance_S{
    unsigned short Mode;
}Remo_Camera_WhiteBalance_s;


#endif // REMOPROTOCOLUTILS_H
