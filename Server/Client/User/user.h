//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_USER_H
#define HTTPSERVER_USER_H

#include "../client.h"
#include <random>

class UserServer : public Client{
public:
    std::string handleClient(HttpRequest &requestParsed) override;

protected:
    bool signIn(std::string &request) override;

    bool signUp(std::string &request);

    uint64_t generateID(std::string &model);

private:
    bool isIdUsed(std::string modelName, uint64_t id);

    UserData getSingInData(std::string data);
};


#endif //HTTPSERVER_USER_H
