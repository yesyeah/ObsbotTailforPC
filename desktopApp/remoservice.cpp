#include "remoservice.h"
#include <bitset>
#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;

RemoService::RemoService(){
    packSeq = 0;
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD( 2, 2 );
    int errNo = WSAStartup( wVersionRequested, &wsaData );
    if ( errNo != 0 ) {
        std::cout<<"error while create remo service"<<std::endl;
    }

    if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) {
        WSACleanup();
        std::cout<<"error while create remo service"<<std::endl;
    }

    std::cout<<"new remo service"<<std::endl;

}

RemoService::~RemoService(){
    closesocket(sockClient);
    WSACleanup();
}

bool RemoService::ApertureASet(){

    return true;
}

bool RemoService::ApertureMSet(){

    return true;
}

bool RemoService::init(){

    //char recvBuf[100];
    //char sendBuf[100];
    //char tempBuf[200];

    //int len = sizeof(SOCKADDR);
   /* while(1){
        gets(sendBuf);
        sendto(sockClient, sendBuf,strlen(sendBuf)+1, 0, (SOCKADDR*)&addrClient, len);
        recvfrom(sockClient, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
    }*/
    std::cout<<"socket init"<<std::endl;
}

bool RemoService::communicateInit(){

}

char* RemoService::dataPack(char data, unsigned short command, char receiver){
    /*package description
      sync head  -   8bit
      version    -   4bit
      frame len  -   12bit
      frame descrip = 8bit
      frame seq  -   16bit
      checksum   -   16bit
      head check -   8bit
      sender     -   4bit
      receiver   -   4bit
      commandset -   4bit
      commandid  -   12bit
    */
    char* communicationData = new  char(REMO_PACK_LEN);
    memset(communicationData, 0 , REMO_PACK_LEN);

    unsigned short frameLen = 0x0;   //dataLen   no data
    unsigned short checkSum = 0;     //crc16
    unsigned char checkBit = 0;      //no use

    //std::bitset<8> syncHead = 0xaa;
    communicationData[0] = 0xaa;

    //std::bitset<4> version = 0;
    //std::bitset<12> frameLength = frameLen & 0xfff;
    communicationData[1] = 0 < 4 || (frameLen & 0x0f00)>>8;
    communicationData[2] = (frameLen & 0x00ff);

    //std::bitset<8> frameDescrip = 0x12;
    communicationData[3] = 0x12;

    /*std::bitset<16> frameSeq = packSeq & 0xffff;
    std::bitset<16> frameCheckSum = checkSum & 0xffff;*/
    communicationData[4] = (packSeq & 0xff00) >> 8;
    communicationData[5] = (packSeq & 0x00ff);
    communicationData[6] = (checkSum & 0xff00) >> 8;
    communicationData[7] = (checkSum & 0x00ff);

    /*std::bitset<8> headCheckBit = checkBit;
    std::bitset<4> sender = (Terminal::Pc & 0xff) < 4;
    std::bitset<4> recv =  receiver & 0x0f;
    std::bitset<4> commandSet = command & 0x0f;
    std::bitset<12> commandID = description & 0x0fff;*/
    communicationData[8] = checkBit;                    //pack head checkbit
    communicationData[9] = (Terminal::Pc & 0xff) < 4  || (receiver & 0xff);
    communicationData[10] = (command & 0xffff0000) > 8;      //command
    communicationData[11] = command & 0xffff;   //description

    //headCheckBit = CRC16_USB(communicationData, 12) & 0x00ff;
    communicationData[8] = Util::CRC16_USB(communicationData, 12) & 0x00ff;
    checkSum = Util::CRC16_USB(communicationData, 12) & 0xffff;
    communicationData[6] = (checkSum & 0xff00) > 8;
    communicationData[7] = (checkSum & 0x00ff);

    packSeq = packSeq + 1;
    std::cout<<"data after pack is : "<<communicationData<<std::endl;
    return communicationData;
}

bool RemoService::dataUnPack(char* data, RemoProcotolHead* response){
    if (response == nullptr){
        return false;
    }
    memset(response, 0, sizeof(RemoProcotolHead));
    memcpy(response, data, sizeof(RemoProcotolHead));

    return true;
}

bool RemoService::request(char command, unsigned short description, char receiver){
    sockClient = socket(AF_INET, SOCK_DGRAM, 0);

    addrClient.sin_addr.S_un.S_addr = inet_addr(REMO_PROCOTOL_ADDRESS);
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(REMO_PROCOTOL_PORT);
    int length  = sizeof(addrClient);

    char* sendBuf = dataPack(command, description, receiver);

    std::cout<<"send buf "<< sendBuf<<" size: "<< strlen(sendBuf)<<std::endl;

    sendto(sockClient, sendBuf, strlen(sendBuf), 0, (SOCKADDR*)&addrClient, sizeof(SOCKADDR));

    char recvData[255];
    int ret = recvfrom(sockClient, recvData, 255, 0, (sockaddr *)&addrClient,&length);
    if(ret > 0) {
       recvData[ret] = 0x00;
       std::cout<< recvData<<std::endl;
    }

    closesocket(sockClient);
    WSACleanup();

    delete  sendBuf;
}

bool RemoService::receive(){

    return true;
}


int RemoService::ApertureCurGet(){

}

bool RemoService::ExposureModeSet(unsigned char mode){
    char data;
    unsigned short cmd = (1 << 12 )| (1 << 9) | (CameraDescription::Exposure & 0x00ff);
    char recevier = Terminal::Camera;

    data = mode;
    std::cout<<"set exposure mode is "<<mode<<std::endl;
    request(data, cmd, recevier);
    return true;
}

bool RemoService::ExposureASet(){


}

bool RemoService::ExposurePSet(){

}

bool RemoService::ExposureSSet(){

}

int RemoService::ExposureCurGet(){
    char data;
    unsigned short cmd = (1 << 12 )| (0 << 9) | (CameraDescription::Exposure & 0x00ff);
    char recevier = Terminal::Camera;

    data = 0;
    request(data, cmd, recevier);
    return true;
}

int RemoService::ExposureCompensationCurGet(){

}

bool RemoService::IsoMSet(unsigned char value){
    char data;
    unsigned short cmd = (1 << 12 )| (1 << 9) | (CameraDescription::IsoM & 0x00ff);
    char recevier = Terminal::Camera;

    data = value;
    request(data, cmd, recevier);
    return true;
}

int RemoService::IsoCurGet(){
    char data;
    unsigned short cmd = (1 << 12 )| (0 << 9) | (CameraDescription::IsoCur & 0x00ff);
    char recevier = Terminal::Camera;

    data = 0;
    request(data, cmd, recevier);
    return true;
}

bool RemoService::ShutterMSet(){
    return true;
}

bool RemoService::ShutterSSet(){
    return true;

}

int RemoService::ShutterCurGet(){
    return 0;
}

int RemoService::WhiteBalanceGet(){
    char data;
    unsigned short cmd = (1 << 12 )| (0 << 9) | (CameraDescription::WhiteBalance & 0x00ff);
    char recevier = Terminal::Camera;

    data = 0;
    request(data, cmd, recevier);
    return true;
}

bool RemoService::WhiteBalanceSet(unsigned char mode){
    char data;
    unsigned short cmd = (1 << 12 )| (1 << 9) | (CameraDescription::WhiteBalance & 0x00ff);
    char recevier = Terminal::Camera;

    data = mode;
    request(data, cmd, recevier);
    return true;
}

/*
bool RemoService::ZoomGet(){

}

bool RemoService::ZoomSet(){

}

bool RemoService::ZoomModeGet(){

}

bool RemoService::ZoomModeSet(){

}
*/
int RemoService::UsbModeGet(){
    char data = 0;
    unsigned short cmd = (1 << 12 )| (0 << 9) | (CameraDescription::Poweroff & 0x0fff);
    char recevier = Terminal::Camera;
    request(data, cmd, recevier);
    return true;
}

bool RemoService::UsbModeSet(bool uvc_mode){
    char data;
    unsigned short cmd = (1 << 12 )| (1 << 9) | (CameraDescription::UsbMode & 0x0fff);
    char recevier = Terminal::Camera;

    if (uvc_mode){
        data = UsbMode::NET;
    } else {
        data = UsbMode::UDisk;
    }

    request(data, cmd, recevier);
    return true;
}

bool RemoService::PowerOff(){
    char data = 0;
    unsigned short cmd = (4 << 12 )| (1 << 9) | (CameraDescription::Poweroff & 0x0fff);
    char recevier = Terminal::Battery;
    request(data, cmd, recevier);
}



