//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "user.h"
#include <cstdlib>
#include<time.h>


std::string UserServer::handleClient(HttpRequest &requestParsed) {
    if(requestParsed.typeRequest==POST){
        bool flag=UserServer::signIn( requestParsed.rawRequest);
        if(!flag) return AUTHENTICATION_ERROR;
    }
    if(requestParsed.method=="signin") return "OK";
    if(requestParsed.method=="AddDevice") {
        uint64_t id=generateID(requestParsed.data);
        return rout.addDevice(requestParsed.data, id);
    }
    return rout.getAnswer(requestParsed);
}

bool UserServer::signIn(std::string &request) {
    return rout.signInUser(getSingInData(request)) == "OK";
}

bool UserServer::signUp(std::string &request) {
    return false;
}

uint64_t UserServer::generateID(std::string &model) {
    uint32_t testID;
    int16_t pos= model.find("modelName");
    if(pos==-1)return 0;
    pos+=strlen("modelName':'");
    std::string model_name;

    while(model[pos]!='"'){
        model_name+=model[pos];
        pos++;
    }
    srand(time(NULL));
    do{
        testID=(uint32_t)rand();
    }while(!isIdUsed(model_name,testID));
    return testID;
}

bool UserServer::isIdUsed(std::string modelName, uint64_t id) {
    if(rout.checkIdProduct(modelName, id)=="OK")return true;
    return false;
}

UserData UserServer::getSingInData(std::string data) {
    UserData info;
    uint64_t pos=data.find("login");
    pos+=strlen("login\":\"");
    while(data[pos]!='"'){
        char a=data[pos];
        info.login+=(a);
        pos++;
    }
    pos=data.find("password");
    pos+=strlen("password\":\"");
    while(data[pos]!='"'){
        info.password.push_back(data[pos]);
        pos++;
    }
    return info;
}
