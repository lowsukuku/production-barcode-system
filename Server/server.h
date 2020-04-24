//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_SERVER_H
#define HTTPSERVER_SERVER_H
#include <thread>
#include "./Client/User/user.h"
#include "./Client/Scaner/scaner.h"
enum ClientType{
    user,
    scaner,
};

class Server {
public:
    void start();

    void stop();

private:
    void acceptor();

    void clientHandler();

    enum ClientType getType();

public:
    std::vector<User> users;
    std::vector<Scaner> devices;
private:
    net::io_context ioc{1};
    tcp::acceptor sock;
};


#endif //HTTPSERVER_SERVER_H
