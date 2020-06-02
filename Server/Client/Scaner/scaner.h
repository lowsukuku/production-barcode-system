//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_SCANER_H
#define HTTPSERVER_SCANER_H


#include "../client.h"

class Scaner : public Client{
public:
    explicit Scaner();

    std::string handleClient(HttpRequest &requestParsed) override;

protected:
    bool signIn(std::string &request) override;

private:
    uint64_t getScanerID(std::string &request);

private:
    uint64_t id;
    Router rout;
};


#endif //HTTPSERVER_SCANER_H
