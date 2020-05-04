//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_CLIENT_H
#define HTTPSERVER_CLIENT_H

#include "../HttpHandler/httphandler.h"


constexpr char AUTHENTICATION_ERROR[]="AUTHENTICATION_ERROR";

class Client {
public:
    virtual std::string handleClient(HttpRequest &requestParsed)=0;

protected:
    virtual bool signIn(std::string &request)=0;
    Router rout;
};


#endif //HTTPSERVER_CLIENT_H
