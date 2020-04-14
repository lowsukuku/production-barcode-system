//
// Created by Daniil Tchyorny on 13.04.2020.
//

#ifndef FINALPROJECT_SERVER_PART_SERVER_H
#define FINALPROJECT_SERVER_PART_SERVER_H

#include <vector>
#include "Client/User/user.h"
#include "Client/Scaner/scaner.h"

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
    boost::asio::io_service serv;
    boost::asio::ip::tcp::endpoint sock;
};


#endif //FINALPROJECT_SERVER_PART_SERVER_H
