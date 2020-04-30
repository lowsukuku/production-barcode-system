//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_SERVER_H
#define HTTPSERVER_SERVER_H
#include <thread>
#include "./Client/User/user.h"
#include "./Client/Scaner/scaner.h"
#include "./HttpHandler/httphandler.h"


class Server {
public:
    explicit Server(std::string &&serverIP="127.0.0.1", unsigned short &&serverPORT=8000);

    void start();

    void stop();

private:
    void accept(tcp::acceptor &&acceptor);

    void clientHandler(tcp::socket &&socket);

public:
    std::vector<User> users;
    std::vector<Scaner> devices;
private:
    std::string ip;
    unsigned short port;
    net::io_context ioc{1};
};


#endif //HTTPSERVER_SERVER_H
