#include "httpservice.h"
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    std::string data((const char*) ptr, (size_t) size * nmemb);
    *((stringstream*) stream) << data << std::endl;
    //std::cout<<"get write data function:"<<data<<std::endl;
    //std::cout <<"get write data size :"<<size*nmemb<<std::endl;
    return size * nmemb;
}

size_t write_data_post(void *ptr, size_t size, size_t nmemb, void *fp) {
    std::string data((const char*) ptr, (size_t) size * nmemb);
    memcpy(fp, data.c_str(), size * nmemb);
    //std::cout<<"post write data function:"<<data<<std::endl;
    //std::cout <<"post write data size :"<<size*nmemb<<std::endl;
    return size * nmemb;
}


static int OnDebug(CURL *, curl_infotype itype, char * pData, size_t size, void *)  {
    if(itype == CURLINFO_TEXT)
    {
        //printf("[TEXT]%s\n", pData);
    }
    else if(itype == CURLINFO_HEADER_IN)
    {
        printf("[HEADER_IN]%s\n", pData);
    }
    else if(itype == CURLINFO_HEADER_OUT)
    {
        printf("[HEADER_OUT]%s\n", pData);
    }
    else if(itype == CURLINFO_DATA_IN)
    {
        printf("[DATA_IN]%s\n", pData);
    }
    else if(itype == CURLINFO_DATA_OUT)
    {
        printf("[DATA_OUT]%s\n", pData);
    }
    return 0;
}

HttpService::HttpService(){
    curl_global_init(CURL_GLOBAL_ALL);
}

bool HttpService::postRequest(std::string url, std::string request, std::string &response){
    CURL* curlHandle = curl_easy_init();
    if (curlHandle == nullptr){
        std::cout<<"curl handle is null, curl post request failed!";
        return -1;
    }

    char* resp = reinterpret_cast<char*>(malloc(2048));
    memset(resp, 0, 2048);
    curl_slist* head_list = nullptr;
    head_list = curl_slist_append(head_list, "Content-Type:application/json");

    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_HTTPPOST, 1L);
    //curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, head_list);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data_post);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, resp);
    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, request.c_str());

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    response = std::string(resp);
    delete  resp;
    return true;
}

bool HttpService::getRequest(std::string url, std::string request, std::string &response){
     CURL* curlHandle = curl_easy_init();

    if (curlHandle == nullptr){
        std::cout<<"curl handle is null, curl request failed!";
        return false;
    }

    std::stringstream resp;
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type:application/json");
    curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlHandle, CURLOPT_HTTPGET, 1L);
    //curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &resp);
    //curl_easy_setopt(curlHandle, CURLOPT_DEBUGFUNCTION, OnDebug);

    curl_easy_perform(curlHandle);
    curl_easy_cleanup(curlHandle);

    response = resp.str();

    headers = nullptr;
    return true;
}

