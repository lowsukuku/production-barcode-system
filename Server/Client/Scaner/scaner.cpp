//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "scaner.h"

Scaner::Scaner(boost::asio::ip::tcp sock) : Client(sock), id(0) {

}

void Scaner::handleClient(std::string request) {

}

bool Scaner::signIn(std::string request) {
    return false;
}

uint64_t Scaner::getScanerID(std::string request) {
    return 0;
}
