//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "user.h"
#include <cstdlib>


std::string User::handleClient(HttpRequest &requestParsed) {
    bool flag=User::signIn( requestParsed.rawRequest);
    if(!flag) return AUTHENTICATION_ERROR;
    return rout.getAnswer(requestParsed);
}

bool User::signIn(std::string &request) {
    if(rout.signInUser(getSingInData(request))=="OK") return true;
    return false;
}

bool User::signUp(std::string &request) {
    return false;
}

uint64_t User::generateID() {
    uint32_t testID;
    do{
        testID=(uint32_t)std::rand();
    }while(!isIdUsed(testID));
    return testID;
}

bool User::isIdUsed(uint64_t id) {
    return false;
}

UserData User::getSingInData(std::string data) {
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
