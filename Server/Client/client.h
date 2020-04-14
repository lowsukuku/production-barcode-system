//
// Created by Daniil Tchyorny on 13.04.2020.
//

#ifndef FINALPROJECT_SERVER_PART_CLIENT_H
#define FINALPROJECT_SERVER_PART_CLIENT_H

#include "../HttpHandler/httphandler.h"

class Client {
public:
    explicit Client(boost::asio::ip::tcp::socket sock=-1);

    virtual bool isClientActive()=0;

    virtual bool singIn()=0;

protected:

    virtual void mainLoop()=0;

    std::string askDataBase(std::string);

protected:
    boost::asio::ip::tcp::socket socket;
};


#endif //FINALPROJECT_SERVER_PART_CLIENT_H
