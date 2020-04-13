//
// Created by Daniil Tchyorny on 13.04.2020.
//

#include "client.h"

Client::Client(boost::asio::ip::tcp::socket sock) {

}

std::string Client::getHTTP() {
    return std::string();
}

std::string Client::parseHTTP(std::string) {
    return std::string();
}

std::string Client::askDataBase(std::string) {
    return std::string();
}

std::string Client::createHTTP(std::string) {
    return std::string();
}

void Client::sendHTTP(std::string) {

}
