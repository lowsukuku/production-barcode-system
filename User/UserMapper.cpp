#include "UserMapper.h"


UserMapper::UserMapper() {

}

err_code UserMapper::signInUser(User &user) {
    return WRONG_LOGIN;
}

err_code UserMapper::signUpUser(User &user) {
    return WRONG_LOGIN;
}

err_code UserMapper::update(User &user) {
    return WRONG_LOGIN;
}

void *UserMapper::deleteUser(User &user) {
    return nullptr;
}

User UserMapper::getById(int id) {
    return User();
}
