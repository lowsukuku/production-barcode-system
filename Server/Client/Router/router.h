//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_ROUTER_H
#define HTTPSERVER_ROUTER_H

#include <iostream>
#include <string>
#include "../../DataBase/src/Parser/IPost.h"
#include "../../DataBase/src/Parser/IGet.h"

enum RequestType{
    POST,
    GET,
};

enum ClientType{
    USER,
    SCANER,
};

struct HttpRequest{
    enum RequestType typeRequest;
    enum ClientType client;
    std::string method;
    uint64_t contentLength;
    std::string data;
    std::string rawRequest;
};

struct UserData{
    std::string login;
    std::string password;
};

class Router {
public:// GET and CHECK methods
    std::string getAnswer(HttpRequest &request);

    std::string  signInScaner(uint64_t apiKey);

    std::string  signInUser(UserData info);

    std::string signUpUser(UserData info);

    std::string getDevicesByID(std::string &request);

    std::string getModels();

    std::string checkIdProduct(std::string modelName, uint64_t id);

    std::string addDevice(std::string &request, uint64_t id);

private:// POST methods

    std::string deleteDevice(std::string &request);

    std::string createModel(std::string &request);

    std::string deleteModel(std::string &request);

    std::string getAllModelsDetailed();

    std::string getAllDevices();

    std::string getDevicesByModel(std::string &request);

    std::string getDevicesIdByModel(std::string &request);

private:
    IPost postRequestHandler;
    IGet getRequestHandler;
};


#endif //HTTPSERVER_ROUTER_H




// TODO authorization
// TODO gernration id in addDevice request and rewrite all method only modelname
// TODO 