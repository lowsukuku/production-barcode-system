//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "httphandler.h"

void HttpHandler::parseRequest(const std::string &request) {

}

RequestType HttpHandler::getRequestType(const std::string &request) {
    return POST;
}

std::string HttpHandler::dataToRequest(const std::string &data) {
    return std::string();
}
