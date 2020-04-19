//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "httphandler.h"

HttpHandler::HttpHandler(boost::asio::ip::tcp sock) :sock(sock){

}

void HttpHandler::getRequest() {

}

void HttpHandler::sendRequest(std::string data) {

}

void HttpHandler::parseRequest(std::string request) {

}

std::string HttpHandler::getRequestType(std::string request) {
    return std::string();
}

std::string HttpHandler::dataToRequest(std::string data) {
    return std::string();
}
