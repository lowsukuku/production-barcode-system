#include "UserMapper.h"


UserMapper::UserMapper() {
    mydb = new DBMySQL;
}

UserMapper::~UserMapper() {
    delete mydb;
}


//    select * from users where name = 'ivan' and surname = 'petrovich';
std::string UserMapper::signInUser(User &user) {
    std::string command =
            "SELECT * FROM users WHERE name = '" + user.getLogin() + "' AND surname = '" + user.getPassword() + "'";
    mydb->executeQuery(command);
    std::string checker;

    std::string s = "name";
    mydb->next();
    try {
        checker = mydb->getString(s);
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return "USER_AUTHENTIFICATION_ERROR";
    }

    return "OK";
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
