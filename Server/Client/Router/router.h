//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_ROUTER_H
#define HTTPSERVER_ROUTER_H

#include <iostream>

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
    std::string getAnswer(HttpRequest request);

    std::string  signInScaner(uint64_t apiKey);

    std::string  signInUser(UserData personalInfo);

    std::string signUpUser(UserData personalInfo);

    std::string getDevices(std::string);

    std::string getModels(std::string);

    std::string checkIdProduct(uint64_t id);

private:// POST methods
    std::string fixDevice(std::string);

    std::string addDevice(std::string);

    std::string deleteDevice(std::string);

    std::string createModel(std::string);

    std::string deleteModel(std::string);

    std::string fixModel(std::string);

private:
    //DbManager db;//Iliya's class object
};


#endif //HTTPSERVER_ROUTER_H
