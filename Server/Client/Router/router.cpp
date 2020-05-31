//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "router.h"

std::string Router::getAnswer(HttpRequest &request) {
    std::string answer;
    if(request.method=="AddDevice") answer = addDevice(request.data);
    else if(request.method=="DeleteDevice") answer = deleteDevice(request.data);
    else if(request.method=="AddModel") answer = createModel(request.data);
//    else if(request.method=="checkIdProduct") answer = checkIdProduct(request.rawRequest);
    else if(request.method=="GetDeviceById") answer = getDevicesByID(request.data);
    else if(request.method=="DeleteModel") answer = deleteModel(request.data);
    else if(request.method=="GetAllModels") answer = getModels();
    else{
        answer ="COMMAND_ERROR";
        std::cerr<<"Undifined command: "<<request.method<<std::endl;
    }
    return answer;
}

std::string Router::addDevice(std::string &request) {
    if(postRequestHandler.addToDB(request))return "OK";
    return "ERROR";
}

std::string Router::deleteDevice(std::string &request) {
    int16_t pos=request.find("\"deviceID\":");
    if(pos==-1)return "ARGUMENT_ERROR";
    pos+=strlen("\"deviceID\":");
    std::string s;
    while(request[pos]!='}' && request[pos]!=' '){
        s.push_back(request[pos]);
        pos++;
    }
    return postRequestHandler.removeProduct(std::stof(s));
}

std::string Router::createModel(std::string &request) {
    int16_t pos=request.find("\"modelName\":");
    if(pos==-1)return "ARGUMENT_ERROR";
    pos+=strlen("\"modelName\":")+1;
    std::string s;
    while(request[pos]!='"'){
        s.push_back(request[pos]);
        pos++;
    }
    postRequestHandler.addMod(s);
    return "OK";
}

std::string Router::deleteModel(std::string &request) {
    int16_t pos=request.find("\"modelName\":");
    if(pos==-1)return "ARGUMENT_ERROR";
    pos+=strlen("\"modelName\":")+1;
    std::string s;
    while(request[pos]!='"'){
        s.push_back(request[pos]);
        pos++;
    }
    postRequestHandler.removeMod(s);
    return "OK";
}

std::string Router::getModels() {
    return getRequestHandler.getAllModels();
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
    return getRequestHandler.getJsonProductByDeviceId(std::stoll(s));
}
