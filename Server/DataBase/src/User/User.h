#ifndef DB_USER_H
#define DB_USER_H


using namespace std;
#include <string>


class User {
private:
    int id;
    string name;
    string surname;
    string login;
    string password;

public:
    User();

    void setName(string &name);
    string getName();

    void setSurname(string &surname);
    string getSurname();

    void setLogin(string &login);
    string getLogin();

    void setPassword(string &password);
    string getPassword();
};


#endif //DB_USER_H
