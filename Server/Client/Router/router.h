//
// Created by Daniil Tchyorny on 15.04.2020.
//

#ifndef FINALPROJECT_SERVER_PART_ROUTER_H
#define FINALPROJECT_SERVER_PART_ROUTER_H

#include <iostream>

class Router {
public:
    std::string parse(std::string);
private:
    std::string  signInUser(std::string);

    std::string signUpUser(std::string);

    std::string  signInScaner(std::string);

    std::string fixDevice(std::string);

    std::string addDevice(std::string);

    std::string deleteDevice(std::string);

    std::string createModel(std::string);

    std::string deleteModel(std::string);

    std::string fixModel(std::string);

    std::string getDevices(std::string);

    std::string checkIdProduct(std::string);

private:
   // DbMannager db;//объект класса Ильи
};


#endif //FINALPROJECT_SERVER_PART_ROUTER_H
