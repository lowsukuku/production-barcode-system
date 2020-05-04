//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "scaner.h"

Scaner::Scaner(){

}

std::string Scaner::handleClient(HttpRequest &requestParsed) {
    id=getScanerID(requestParsed.rawRequest);
    if(!signIn(requestParsed.rawRequest))return AUTHENTICATION_ERROR;
    return rout.getAnswer(requestParsed);
}

bool Scaner::signIn(std::string &request) {
    if(rout.signInScaner(id)=="OK") return true;
    return false;
}

uint64_t Scaner::getScanerID(std::string &request) {
    int64_t pos=request.find("apiKey");
    if(pos==-1)
        return 0;
    pos+=2;
    std::string apiKey;
    while(request[pos]!=','){
        apiKey.push_back(request[pos]);
    }
    return std::atoi(apiKey.c_str());
}
