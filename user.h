//
// Created by Daniil Tchyorny on 13.04.2020.
//

#ifndef FINALPROJECT_SERVER_PART_USER_H
#define FINALPROJECT_SERVER_PART_USER_H

#include "client.h"

class User : public Client{
public:
    User();

protected:

    bool singIn() override;

    bool singUp();

    uint64_t generateID();

    bool isIDUsed();

    void mainLoop() override;

    void saveExit();

    bool isClientActive() override;

public:
    std::string login;
};


#endif //FINALPROJECT_SERVER_PART_USER_H
