//
// Created by Daniil Tchyorny on 13.04.2020.
//

#ifndef FINALPROJECT_SERVER_PART_USER_H
#define FINALPROJECT_SERVER_PART_USER_H

#include "../client.h"

class User : public Client{
public:
    User();

    bool singIn() override;

    bool singUp();

    uint64_t generateID();

    void saveExit();

    bool isClientActive() override;

protected:

    bool isIDUsed();

    void mainLoop() override;

public:
    std::string login;
};


#endif //FINALPROJECT_SERVER_PART_USER_H
