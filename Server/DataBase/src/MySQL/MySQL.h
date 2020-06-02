#ifndef DB_MYSQL_H
#define DB_MYSQL_H


#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class DBMySQL {
private:
    sql::Connection *con;
    sql::Driver *driver;
    sql::Statement *stmt;
    sql::ResultSet  *res;
public:
    DBMySQL(const char* filename = "config.cfg");
    ~DBMySQL();

    bool execute(std::string& query);
    sql::ResultSet* executeQuery(std::string& query);
    bool next();
    int getInt(int ind);
    int getRow();
    sql::SQLString getString(std::string& colLabel);
};

#endif //DB_MYSQL_H
