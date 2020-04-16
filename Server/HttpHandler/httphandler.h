//
// Created by Daniil Tchyorny on 14.04.2020.
//

#ifndef FINALPROJECT_SERVER_PART_HTTPHANDLER_H
#define FINALPROJECT_SERVER_PART_HTTPHANDLER_H

#include <iostream>

struct HttpInfo{
    std::string request;
    std::string header;
    std::string body;
};


class HttpHandler {
public:
    std::string getHTTP();

    HttpInfo parseHTTP(std::string);

    std::string createHTTP(std::string);

    void sendHTTP(std::string);
};


#endif //FINALPROJECT_SERVER_PART_HTTPHANDLER_H
