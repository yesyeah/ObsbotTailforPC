#ifndef HTTP_SERVICE_H
#define HTTP_SERVICE_H
#include "curl/curl.h"
#include "curl/easy.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <stdio.h>
#include <share.h>

class HttpService{
public:
    HttpService();
    ~HttpService() = default;

    bool postRequest(std::string url, std::string request, std::string &response);
    bool getRequest(std::string url, std::string request,  std::string &response);
};

#endif
