//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "scaner.h"

Scaner::Scaner(){

}

std::string Scaner::handleClient(HttpRequest &requestParsed) {
    id=getScanerID(requestParsed.rawRequest);
    if(!signIn(requestParsed.rawRequest))return AUTHENIFICATION_ERROR;
    return rout.getAnswer(requestParsed);
}

bool Scaner::signIn(std::string &request) {
    if(rout.signInScaner(id)=="OK") return true;
    return false;
}

uint64_t Scaner::getScanerID(std::string &request) {
    size_t pos=request.find("apiKey");
    pos+=2;
    std::string apiKey;
    while(request[pos]!=','){
        apiKey.push_back(request[pos]);
    }
    return std::atoi(apiKey.c_str());
}
