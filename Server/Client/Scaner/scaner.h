//
// Created by Daniil Tchyorny on 13.04.2020.
//

#ifndef FINALPROJECT_SERVER_PART_SCANER_H
#define FINALPROJECT_SERVER_PART_SCANER_H

#include "../client.h"
class Scaner : public Client{
public:
    Scaner();

    bool singIn() override;

    bool isClientActive() override;

protected:
    void mainLoop() override;

public:
    uint64_t id;
private:
    time_t lastActiveTime;

};


#endif //FINALPROJECT_SERVER_PART_SCANER_H
