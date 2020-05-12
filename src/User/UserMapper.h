#ifndef DB_USERMAPPER_H
#define DB_USERMAPPER_H


#include "User.h"
#include "../err_code.h"


class UserMapper {
private:
    void *dataBase; // обьект базы данных TO DO поменять тип

public:
    UserMapper();

    err_code signInUser(User &user);
    err_code signUpUser(User &user);

    err_code update(User &user);
    void *deleteUser(User &user);

    User getById(int id);

};


#endif //DB_USERMAPPER_H
