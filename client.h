//
// Created by Daniil Tchyorny on 13.04.2020.
//

#ifndef FINALPROJECT_SERVER_PART_CLIENT_H
#define FINALPROJECT_SERVER_PART_CLIENT_H

#include <iostream>

class Client {
public:
    explicit Client(boost::asio::ip::tcp::socket sock=-1);

    virtual bool isClientActive()=0;

protected:

    virtual bool singIn()=0;

    virtual void mainLoop()=0;

    std::string getHTTP();

    std::string parseHTTP(std::string);

    std::string askDataBase(std::string);

    std::string createHTTP(std::string);

    void sendHTTP(std::string);

protected:
    boost::asio::ip::tcp::socket socket;
};


#endif //FINALPROJECT_SERVER_PART_CLIENT_H
