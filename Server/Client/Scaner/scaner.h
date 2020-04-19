//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_SCANER_H
#define HTTPSERVER_SCANER_H


#include "../client.h"
class Scaner : public Client{
public:
    explicit Scaner(boost::asio::ip::tcp sock);

    void handleClient(std::string request) override;

protected:
    bool signIn(std::string request) override;

private:
    uint64_t getScanerID(std::string request);

private:
    uint64_t id;
};


#endif //HTTPSERVER_SCANER_H
