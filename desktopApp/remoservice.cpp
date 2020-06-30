#include "remoservice.h"
#include <bitset>

using namespace std;
extern unsigned short CRC16_USB(unsigned char *data, unsigned int datalen);

RemoService::RemoService(){
    packSeq = 0;
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD( 1, 1 );
    int errNo = WSAStartup( wVersionRequested, &wsaData );
    if ( errNo != 0 ) {
        std::cout<<"error while create remo service"<<std::endl;
    }

    if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) {
        WSACleanup();
        std::cout<<"error while create remo service"<<std::endl;
    }

}

RemoService::~RemoService(){
    WSACleanup();
}

bool RemoService::ApertureASet(){

    return true;
}

bool RemoService::ApertureMSet(){

    return true;
}

bool RemoService::init(){


    SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
    SOCKADDR_IN addrClient;
    addrClient.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(6000);

    char recvBuf[100];
    char sendBuf[100];
    char tempBuf[200];


    int len = sizeof(SOCKADDR);
    while(1){
        gets(sendBuf);
        sendto(sockClient, sendBuf,strlen(sendBuf)+1, 0, (SOCKADDR*)&addrClient, len);
        recvfrom(sockClient, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
    }

    closesocket(sockClient);
}

bool RemoService::communicateInit(){

}

unsigned char* RemoService::dataPack(char command, unsigned short description, char receiver){
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
    unsigned char* communicationData = new unsigned char(REMO_PACK_LEN);
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
    communicationData[10] = (command & 0xff) < 4  || (description & 0xff00) > 8;      //command
    communicationData[11] = description & 0x00ff;   //description

    //headCheckBit = CRC16_USB(communicationData, 12) & 0x00ff;
    communicationData[8] = Util::CRC16_USB(communicationData, 12) & 0x00ff;
    checkSum = Util::CRC16_USB(communicationData, 12) & 0xffff;
    communicationData[6] = (checkSum & 0xff00) > 8;
    communicationData[7] = (checkSum & 0x00ff);

    packSeq = packSeq + 1;
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

bool RemoService::ApertureCurGet(){

}

bool RemoService::ExposureASet(){

}

bool RemoService::ExposurePSet(){

}

bool RemoService::ExposureSSet(){

}

bool RemoService::ExposureCurGet(){

}

bool RemoService::ExposureCompensationCurGet(){

}

bool RemoService::IsoMSet(){

}

bool RemoService::IsoCurGet(){

}

bool RemoService::ShutterMSet(){

}

bool RemoService::ShutterSSet(){

}

bool RemoService::ShutterCurGet(){

}

bool RemoService::WhiteBalanceGet(){

}

bool RemoService::WhiteBalanceSet(){

}

bool RemoService::ZoomGet(){

}

bool RemoService::ZoomSet(){

}

bool RemoService::ZoomModeGet(){

}

bool RemoService::ZoomModeSet(){

}



