//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_HTTPHANDLER_H
#define HTTPSERVER_HTTPHANDLER_H

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

enum RequestType{
    POST,
    GET,
};

struct HttpRequest{
    enum RequestType type;
    std::string method;
    uint64_t contentLength;
    std::string data;
};

class HttpHandler {
public:
    void parseRequest(const std::string &request);

    RequestType getRequestType(const std::string &request);

    std::string dataToRequest(const std::string &data);

public:
    HttpRequest request;
};


#endif //HTTPSERVER_HTTPHANDLER_H
