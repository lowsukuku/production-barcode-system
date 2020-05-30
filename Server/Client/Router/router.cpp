//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "router.h"

std::string Router::getAnswer(HttpRequest &request) {
    std::string answer;
    if(request.method=="addDevice") answer = addDevice(request.rawRequest);
    else if(request.method=="deleteDevice") answer = deleteDevice(request.rawRequest);
    else if(request.method=="fixDevice") answer = fixDevice(request.rawRequest);
    else if(request.method=="createModel") answer = createModel(request.rawRequest);
    else if(request.method=="deleteModel") answer = deleteModel(request.rawRequest);
    else if(request.method=="fixModel") answer = fixModel(request.rawRequest);
    else if(request.method=="checkIdProduct") answer = checkIdProduct(std::stoll(request.rawRequest));
    else{
        return addDevice(request.data);
        answer ="ERROR";
        std::cerr<<"Undifined command: "<<request.method<<std::endl;
    }
    return answer;
}

std::string Router::fixDevice(std::string &request) {
    return std::string();
}

std::string Router::addDevice(std::string &request) {
    if(postRequestHandler.addToDB(request))return "OK";
    return "ERROR";
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

std::string Router::signInUser(UserData info) {
    return "OK";
}

std::string Router::signUpUser(UserData info) {
    return std::string();
}

std::string Router::signInScaner(uint64_t apiKey) {
    return std::string();
}
