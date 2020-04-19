//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_ROUTER_H
#define HTTPSERVER_ROUTER_H

#include <iostream>


class Router {
public:
    std::string getAnswer(std::string body);

private:
    std::string fixDevice(std::string);

    std::string addDevice(std::string);

    std::string deleteDevice(std::string);

    std::string createModel(std::string);

    std::string deleteModel(std::string);

    std::string fixModel(std::string);

    std::string getDevices(std::string);

    std::string getModels(std::string);

    std::string checkIdProduct(std::string);

private:
    //DbManager db;//Iliya's class object
};


#endif //HTTPSERVER_ROUTER_H
