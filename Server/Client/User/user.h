//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_USER_H
#define HTTPSERVER_USER_H

#include "../client.h"
#include "../Router/router.h"
struct UserData{
    std::string login;
    std::string password;
};

class User : public Client{
public:
    void handleClient(std::string request) override;

protected:
    bool signIn(std::string request) override;

    bool signUp(std::string request);

    uint64_t generateID();

private:
    bool isIdUsed();

    UserData getSingInData(std::string data);

private:
    Router rout;
    UserData personalInfo;
};


#endif //HTTPSERVER_USER_H
