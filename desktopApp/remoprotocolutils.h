#ifndef REMO_PROTOCOL_UTILS_H
#define REMO_PROTOCOL_UTILS_H
#include <map>
void InvertUint8(unsigned char *dBuf,unsigned char *srcBuf);
void InvertUint16(unsigned short *dBuf,unsigned short *srcBuf);
void InvertUint32(unsigned int *dBuf,unsigned int *srcBuf);
unsigned short CRC16_USB(unsigned char *data, unsigned int datalen);

enum MainCommand{
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
    //UsbMode = 0x76,
    UsbMode = 0xf6,
    Poweroff = 0x1c2,
};

enum CommandSet{
    GeneralSet = 0,
    CameraSet,
    GimbalSet,
    AlgorithmSet,
    BatterySet,
    ActiveSet,
    FactorySet,
    UpdateSet,
};

enum Terminal{
    Camera = 1,
    Gimbal,
    Algorithm,
    Battery,
    App,
    Pc,
    Device,
    Brocast = 0xf,
};


enum AICommand{
    GimbalCtlTirgger = 0x21,
    ZoomSet = 0x47,
};

enum BatteryCommand{
    TurnOff = 0x88,

};

enum WhiteBalanceMode{
    AUTO = 0,
    INCANDESCENT = 1,
    FLUORESCENT = 2,
    SUNNY =3,
    WINDY = 4,
    CUSTOM = 5,
};

enum ExposureMode{
    P = 0,
    S,
    M,
};

enum AFMode{
    MF = 0,
    AFS,
    AFC
};

enum UsbMode{
    NET = 0,
    UDisk
};

/*enum ISOValue{
    ISO_100 = 0,
    ISO_200,
    ISO_400,
    ISO_800,
    ISO_1600,
    ISO_3200,
    ISO_6400,
    ISO_12800,
    ISO_25600,
};*/
/*
std::map<int,  int> ISOValue{
    {100, 0}, {200, 1}, {400, 2}, {800, 3}, {1600, 4}, {3200, 5}, {6400, 6},
    {12800, 7}, {25600, 8}
};*/

//0-   1/8000      1-   1/6400      2-  1/5000   3-  1/4000   4-  1/3200
//5-   1/2500      6-   1/2000      7-  1/1600   8-  1/1250   9-  1/1000
//10-  1/800       11-  1/640       12- 1/500    13- 1/400    14- 1/320
//15-  1/240       16-  1/200       17- 1/160    18- 1/120    19- 1/100
//20-  1/80        21-  1/60        22- 1/50     23- 1/40     24- 1/30
//25-  1/25        26-  1/20        27- 1/15     28- 1/12.5   29- 1/10
//30-  1/8         31-  1/6.25      32- 1/5      33- 1/4      34- 1/3
//35-  1/2.5       36-  1/2         37- 1/1.67   38- 1/1.25   39- 1
//40-  1.3         41-  1.6         42- 2        43- 2.5      44- 3
//45-  3.2         46-  4           47- 5        48- 6        49- 7
//50-  8           51-  9           52- 10       53- 13       54- 15
/*std::map<int,  std::string> ShutterMode{
    {0, "1/8000"}, {1, "1/6400"}, {2, "1/5000"}, {3, "1/4000"}, {4, "1/3200"},
    {5, "1/2500"}, {6, "1/2000"}, {7, "1/1600"}, {8, "1/1250"}, {9, "1/1000"},
    {10, "1/800"}, {11, "1/640"}, {12, "1/500"}, {13, "1/400"}, {14, "1/320"},
    {15, "1/240"}, {16, "1/200"}, {17, "1/160"}, {18, "1/120"}, {19, "1/100"},
    {20,  "1/80"}, {21,  "1/60"}, {22,  "1/50"}, {23,  "1/40"}, {24,  "1/30"},
    {25,  "1/25"}, {26,  "1/20"}, {27,  "1/15"}, {28,"1/12.5"}, {29,  "1/10"},
    {30,   "1/8"}, {31,"1/6.25"}, {32,   "1/5"}, {33,   "1/4"}, {34,   "1/3"},
    {35, "1/2.5"}, {36,   "1/2"}, {37,"1/1.67"}, {38,"1/1.25"}, {39,     "1"},
    {40,   "1.3"}, {41,   "1.6"}, {42,     "2"}, {43,   "2.5"}, {44,     "3"},
    {45,   "3.2"}, {46,     "4"}, {47,     "5"}, {48,     "6"}, {49,     "7"},
    {50,     "8"}, {51,     "9"}, {52,    "10"}, {53,    "13"}, {54,    "15"}
};*/

typedef struct Remo_Camera_WhiteBalance_S{
    unsigned short Mode;    //0-auto    1-incandescent   2-fluorescent    3-sunny   4-windy    5-custom
}Remo_Camera_WhiteBalance_s;

typedef struct Remo_Camera_AeMode_S{
    unsigned short Mode;      //  0-p   1-s   2-m
}Remo_Camera_AeMode_s;

typedef struct Remo_Camera_Evbias_S{
    unsigned short BIAS;      //0- -3.0    1-  -2.7   2-  -2.3   3-  -2.0    4-  -1.7   5-  -1.3
                              //6-    -1   7-  -0.7   8-  -0.3   9-  0       10- 0.3    11- 0.7
                              //12-   1    13- 1.3    14- 1.7    15- 2.0     16- 2.3    17- 2.7    18- 3.0
}Remo_Camera_Evbias_s;

typedef struct Remo_Camera_Shutter_S{
    unsigned short ShutterTime;    //0-   1/8000      1-   1/6400      2-  1/5000   3-  1/4000   4-  1/3200
                                   //5-   1/2500      6-   1/2000      7-  1/1600   8-  1/1250   9-  1/1000
                                   //10-  1/800       11-  1/640       12- 1/500    13- 1/400    14- 1/320
                                   //15-  1/240       16-  1/200       17- 1/160    18- 1/120    19- 1/100
                                   //20-  1/80        21-  1/60        22- 1/50     23- 1/40     24- 1/30
                                   //25-  1/25        26-  1/20        27- 1/15     28- 1/12.5   29- 1/10
                                   //30-  1/8         31-  1/6.25      32- 1/5      33- 1/4      34- 1/3
                                   //35-  1/2.5       36-  1/2         37- 1/1.67   38- 1/1.25   39- 1
                                   //40-  1.3         41-  1.6         42- 2        43- 2.5      44- 3
                                   //45-  3.2         46-  4           47- 5        48- 6        49- 7
                                   //50-  8           51-  9           52- 10       53- 13       54- 15
                                   //55-  20          56-  25          57- 30
}Remo_Camera_Shutter_s;

typedef struct Remo_Camera_Aperture_S{
    unsigned short Aperture;     //0-  FNO.1    1-   FNO.1.4     2-  FNO.2      3-   FNO.2.8    4-   FNO.4
}Remo_Camera_Aperture_s;

typedef struct Remo_Camera_ISO_S{
    unsigned short ISOValue;
}Remo_Camera_ISO_s;

typedef struct Remo_Camera_AFMode_S{
    unsigned short APMode;
}Remo_Camera_AFMode_s;

typedef struct Remo_Camera_PosPoint_S{
    float x;
    float y;
}Remo_Camera_PosPoint_s;

typedef struct Remo_Camera_PosArea_S{
    Remo_Camera_PosPoint_s Update_Left;
    Remo_Camera_PosPoint_s Down_Right;
}Remo_Camera_PosArea_s;
#endif // REMOPROTOCOLUTILS_H
