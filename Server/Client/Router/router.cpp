//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "router.h"

std::string Router::getAnswer(HttpRequest &request) {
    if(request.method=="addDevice") addDevice(request.rawRequest);
    else if(request.method=="deleteDevice") deleteDevice(request.rawRequest);
    else if(request.method=="fixDevice") fixDevice(request.rawRequest);
    else if(request.method=="createModel") createModel(request.rawRequest);
    else if(request.method=="deleteModel") deleteModel(request.rawRequest);
    else if(request.method=="fixModel") fixModel(request.rawRequest);
    else if(request.method=="checkIdProduct") checkIdProduct(std::stoll(request.rawRequest));
    return std::string();
}

std::string Router::fixDevice(std::string &request) {
    return std::string();
}

std::string Router::addDevice(std::string &request) {
    return std::string();
}

std::string Router::deleteDevice(std::string &request) {
    return std::string();
}

std::string Router::createModel(std::string &request) {
    return std::string();
}

std::string Router::deleteModel(std::string &request) {
    return std::string();
}

std::string Router::fixModel(std::string &request) {
    return std::string();
}

std::string Router::getDevices(std::string &request) {
    return std::string();
}

std::string Router::getModels(std::string &request) {
    return std::string();
}

std::string Router::checkIdProduct(uint64_t id) {
    return std::string();
}

std::string Router::signInUser(UserData &personalInfo) {
    return std::string();
}

std::string Router::signUpUser(UserData &personalInfo) {
    return std::string();
}

std::string Router::signInScaner(uint64_t apiKey) {
    return std::string();
}
