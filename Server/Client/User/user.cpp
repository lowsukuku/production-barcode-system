//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "user.h"
#include <cstdlib>


std::string User::handleClient(HttpRequest &requestParsed) {
    requestParsed.rawRequest;
    bool flag=User::signIn( requestParsed.rawRequest);
    if(!flag) return AUTHENTICATION_ERROR;
    return rout.getAnswer(requestParsed);
}

bool User::signIn(std::string &request) {
    getSingInData(request);
    if(rout.signInUser(personalInfo)=="OK") return true;
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

void User::getSingInData(std::string data) {
    uint64_t pos=data.find("login");
    pos+=strlen("login\":\"");
    while(data[pos]!='"'){
        char a=data[pos];
        personalInfo.login+=(a);
        pos++;
    }
    pos=data.find("password");
    pos+=strlen("password\":\"");
    while(data[pos]!='"'){
        personalInfo.password.push_back(data[pos]);
        pos++;
    }
}
