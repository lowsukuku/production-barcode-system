//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "user.h"

bool User::signIn(std::string) {
    return false;
}

bool User::signUp(std::string request) {
    return false;
}

void User::handleClient(std::string request) {

}

uint64_t User::generateID() {
    return 0;
}

bool User::isIdUsed() {
    return false;
}

UserData User::getSingInData(std::string data) {
    return UserData();
}
