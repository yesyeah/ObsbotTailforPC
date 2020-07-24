#include "utils.h"
#include <string>
#include <iostream>
#include <locale>
#include <codecvt>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

std::string Util::string_To_UTF8(const std::string & str)
{
    int nwLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

    wchar_t * pwBuf = new wchar_t[nwLen + 1];
    ZeroMemory(pwBuf, nwLen * 2 + 2);

    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

    char * pBuf = new char[nLen + 1];
    ZeroMemory(pBuf, nLen + 1);

    WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr(pBuf);

    delete []pwBuf;
    delete []pBuf;

    pwBuf = nullptr;
    pBuf  = nullptr;

    return retStr;
}

QString Util::GBK2UTF8(const QString &str)
{
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    return utf8->toUnicode(str.toUtf8());
}

QString Util::UTF82GBK(const QString &str)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
    return gbk->toUnicode(str.toLocal8Bit());
}

std::string Util::GBK2UTF8(std::string &str)
{
    QString temp = QString::fromLocal8Bit(str.c_str());
    std::string ret = temp.toUtf8().data();
    return ret;
}

std::string Util::UTF82GBK(std::string &str)
{
    QString temp = QString::fromUtf8(str.c_str());
    std::string ret = temp.toLocal8Bit().data();
    return ret;
}

void Util::InvertUint8(unsigned char *dBuf,unsigned char *srcBuf){
    int i;
    unsigned char tmp[4]={0};
    for(i=0; i< 8; i++){
        if(srcBuf[0] & (1 << i))
            tmp[0]|=1<<(7-i);
    }
    dBuf[0] = tmp[0];

}

void Util::InvertUint16(unsigned short *dBuf,unsigned short *srcBuf){
    int i;
    unsigned short tmp[4]={0};

    for(i=0;i< 16;i++)
    {
        if(srcBuf[0]& (1 << i))
            tmp[0]|=1<<(15 - i);
    }
    dBuf[0] = tmp[0];
}

void Util::InvertUint32(unsigned int *dBuf,unsigned int *srcBuf){
    int i;
    unsigned int tmp[4]={0};

    for(i=0;i< 32;i++)
    {
        if(srcBuf[0]& (1 << i))
            tmp[0]|=1<<(31 - i);
    }
    dBuf[0] = tmp[0];

}

unsigned short Util::CRC16_USB(char *data, unsigned int datalen){
    unsigned short wCRCin = 0xFFFF;
    unsigned short wCPoly = 0x8005;

    InvertUint16(&wCPoly,&wCPoly);
    while (datalen--)
    {
        wCRCin ^= *(data++);
        for(int i = 0;i < 8;i++)
        {
            if(wCRCin & 0x01)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin = wCRCin >> 1;
        }
    }
    return (wCRCin^0xFFFF);
}




