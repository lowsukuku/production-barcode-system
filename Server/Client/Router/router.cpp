//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "router.h"

std::string Router::getAnswer(HttpRequest &request) {
    std::string answer;
    if(request.method=="DeleteDevice") answer = deleteDevice(request.data);
    else if(request.method=="AddModel") answer = createModel(request.data);
    else if(request.method=="GetDeviceById") answer = getDevicesByID(request.data);
    else if(request.method=="DeleteModel") answer = deleteModel(request.data);
    else if(request.method=="GetAllModels") answer = getModels();
    else if(request.method=="GetAllModelsDetailed") answer = getAllModelsDetailed();
    else if(request.method=="allDevice") answer=getAllDevices();
    else if(request.method=="devicesByModel") answer=getDevicesByModel(request.data);
    else if(request.method=="getDeviseById") answer=getDevicesByID(request.data);
    else if(request.method=="devicesIdByModel") answer=getDevicesIdByModel(request.data);
    else{
        answer ="COMMAND_ERROR";
        std::cerr<<"Undifined command: "<<request.method<<std::endl;
    }
    return answer;
}

std::string Router::getDevicesIdByModel(std::string &request) {
    if(request.find("model=")==-1)return "ARGUMENT_ERROR";
    uint16_t pos=strlen("model=");
    std::string model;
    for(;request[pos]!='&';++pos){
        model.push_back(request[pos]);
    }
    return getRequestHandler.deviceIdByModel(model);
}

std::string Router::getDevicesByModel(std::string &request) {
    uint16_t pos=strlen("model=");
    std::string model;
    for(;pos<request.size();++pos)
        model.push_back(request[pos]);
    return getRequestHandler.deviceByModel(model);
}

std::string Router::getAllDevices() {
    return getRequestHandler.AllDevices();
}


std::string Router::getAllModelsDetailed() {
    return getRequestHandler.getModDet();
}

std::string Router::addDevice(std::string &request, uint64_t id) {
    int16_t pos= request.find("modelName");
    if(pos==-1)return 0;
    pos+=strlen("modelName':'");
    std::string model_name;

    while(request[pos]!='"'){
        model_name+=request[pos];
        pos++;
    }
    if(postRequestHandler.addToDB(id, model_name))return std::to_string(id);
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
    return postRequestHandler.addMod(s);;
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

    return postRequestHandler.removeMod(s);
}

std::string Router::getModels() {
    return getRequestHandler.getAllModels();
}

std::string Router::checkIdProduct(std::string modelName, uint64_t id) {
    return postRequestHandler.checkProductID(id, modelName);
}

std::string Router::signInUser(UserData info) {
    return postRequestHandler.signIn(info.login, info.password);
}

std::string Router::signUpUser(UserData info) {
    return std::string();
}

std::string Router::signInScaner(uint64_t apiKey) {
    return std::string();
}

std::string Router::getDevicesByID(string &request) {

    int16_t pos=request.find("&id=");
    if(pos==-1)return "ARGUMENT_ERROR";
    pos+=strlen("&id=");
    std::string s;
    for(;pos<request.size();++pos){
        s.push_back(request[pos]);
    }
    if(request.find("model=")==-1)return "ARGUMENT_ERROR";
    pos=strlen("model=");
    std::string model;
    for(;request[pos]!='&';++pos){
        model.push_back(request[pos]);
    }

    return getRequestHandler.getJsonProductByDeviceId(std::stoll(s), model);
}

