#include "User.h"


User::User() {

}

void User::setName(string &name) {
    this->name=name;
}

string User::getName() {
    return this->name;
}

void User::setSurname(string &surname) {
    this->surname=surname;
}

string User::getSurname() {
    return this->surname;
}

void User::setLogin(string &login) {
    this->login=login;
}

string User::getLogin() {
    return this->login;
}

void User::setPassword(string &password) {
    this->password=password;
}

string User::getPassword() {
    return this->password;
}
