//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_CLIENT_H
#define HTTPSERVER_CLIENT_H

#include "../HttpHandler/httphandler.h"

class Client {
public:
    explicit Client(tcp sock): sock(sock), worker(nullptr){}

    virtual void handleClient(std::string request)=0;

protected:
    std::string getPostAnswer(std::string request);

    std::string askDataBase(std::string request);

    virtual bool signIn(std::string request)=0;

protected:
    tcp sock;
    HttpHandler *worker;
};


#endif //HTTPSERVER_CLIENT_H
