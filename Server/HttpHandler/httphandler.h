//
// Created by Daniil Tchyorny on 14.04.2020.
//

#ifndef FINALPROJECT_SERVER_PART_HTTPHANDLER_H
#define FINALPROJECT_SERVER_PART_HTTPHANDLER_H

#include <iostream>

class HttpHandler {
public:
    std::string getHTTP();

    std::string parseHTTP(std::string);

    std::string createHTTP(std::string);

    void sendHTTP(std::string);
};


#endif //FINALPROJECT_SERVER_PART_HTTPHANDLER_H
