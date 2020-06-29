#ifndef REMO_SERVICE_H
#define REMO_SERVICE_H
#include <iostream>
#include <winsock2.h>
#include "remoprotocolutils.h"
#pragma pack (4)

#define REMO_PROCOTOL_ADDRESS "192.168.0.20"
#define REMO_PROCOTOL_PORT 9999
#define REMO_PACK_LEN  96

struct RemoProcotolHead{
    unsigned short syncHead;   //0xAA
    unsigned char version;     //0
    unsigned char length[3];   //data length
    unsigned short describe;   //null
    unsigned int packSeq;      // ++1
    unsigned int checkSum;     //crc16
    unsigned int headCheck;     //12bytes checksum
    unsigned char sender;       //pc-6
    unsigned char receiver;     //camera-1   gimbal-2  battery-4
    unsigned char commandSet;   //univer-0  camera-1 gimbal-2 battery-4
    unsigned char commandId[3];  //main 9bits, other3bits
};

struct RemoProcotolData{

};

enum ReturnValue{
    RETURN_OK = 0,
    RETURN_NG = -1,
    RETURN_PARAM_ERROR = -2,
};

class RemoService{
public:
    RemoService();
    ~RemoService();

    bool init();

    bool communicateInit();

    unsigned char* dataPack(char command, unsigned short description, char receiver);
    bool dataUnPack(char* data, RemoProcotolHead* response);

    bool ExposureCurGet();
    bool ApertureCurGet();
    bool ShutterCurGet();
    bool IsoCurGet();
    bool ExposureCompensationCurGet();

    bool ExposureSSet();
    bool ExposureASet();
    bool ExposurePSet();

    bool ShutterSSet();
    bool ShutterMSet();

    bool WhiteBalanceSet();
    bool WhiteBalanceGet();

    bool ApertureASet();
    bool ApertureMSet();

    bool IsoMSet();

    bool ZoomModeSet();
    bool ZoomModeGet();

    bool ZoomSet();
    bool ZoomGet();

    bool UsbModeSet();
    bool UsbModeGet();

private:
    int exposureType;
    unsigned short packSeq;
};

#endif
