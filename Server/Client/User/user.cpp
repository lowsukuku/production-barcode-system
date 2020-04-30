//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "user.h"


std::string User::handleClient(HttpRequest &requestParsed) {
    if(!signIn(requestParsed.rawRequest)) return AUTHENIFICATION_ERROR;
    return "";
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
        testID=arc4random();
    }while(!isIdUsed(testID));
    return testID;
}

bool User::isIdUsed(uint64_t id) {
    return false;
}

UserData User::getSingInData(std::string &data) {
    uint64_t pos=data.find("login");
    pos+=8;
    while(data[pos]!='"'){
        personalInfo.login.push_back(data[pos]);
        pos++;
    }
    pos=data.find("password");
    pos+=11;
    while(data[pos]!='"'){
        personalInfo.password.push_back(data[pos]);
        pos++;
    }
    return UserData();
}
