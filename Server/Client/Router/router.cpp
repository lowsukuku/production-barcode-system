//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "router.h"

std::string Router::getAnswer(HttpRequest &request) {
    std::string answer;
    if(request.method=="AddDevice") answer = addDevice(request.data);
    else if(request.method=="DeleteDevice") answer = deleteDeviceById(request.data);
    else if(request.method=="fixDevice") answer = fixDevice(request.rawRequest);
    else if(request.method=="createModel") answer = createModel(request.rawRequest);
    else if(request.method=="deleteModel") answer = deleteModel(request.rawRequest);
    else if(request.method=="fixModel") answer = fixModel(request.rawRequest);
    else if(request.method=="checkIdProduct") answer = checkIdProduct(request.rawRequest);
    else if(request.method=="GetDeviceById") answer = getDevicesByID(request.data);
    else{
        answer ="COMMAND_ERROR";
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

std::string Router::deleteDeviceById(std::string &request) {
    if(request.find("id=")==-1)return "ARGUMENT_ERROR";
    uint16_t pos=strlen("id=");
    std::string s;
    for(;pos<request.size();++pos){
        s.push_back(request[pos]);
    }
    return getRequestHandler.removeProduct(std::stof(s));
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

std::string Router::getModels(std::string &request) {
    return std::string();
}

std::string Router::checkIdProduct(std::string data) {
    if(data.find("id=")==-1)return "ARGUMENT_ERROR";
    uint16_t pos=strlen("id=");
    std::string s;
    for(;pos<data.size();++pos){
        s.push_back(data[pos]);
    }
    return getRequestHandler.getJsonProductByDeviceId(std::stof(s));
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

std::string Router::getDevicesByID(string &request) {
    if(request.find("id=")==-1)return "ARGUMENT_ERROR";
    uint16_t pos=strlen("id=");
    std::string s;
    for(;pos<request.size();++pos){
        s.push_back(request[pos]);
    }
    return getRequestHandler.getJsonProductByDeviceId(std::stof(s));
}
