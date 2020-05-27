#include "MySQL.h"


DBMySQL::DBMySQL(const char *filename)
{
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306","newuser","123456789Qqw_!");

    stmt = con->createStatement();
    stmt->execute("USE Scaner");
}

DBMySQL::~DBMySQL()
{
    delete res;
    delete stmt;
    delete con;
}

bool DBMySQL::execute(std::string& query)
{
    bool flag=stmt->execute(query);
    return flag;
}

sql::ResultSet* DBMySQL::executeQuery(std::string& query)
{
    res = stmt->executeQuery(query);
    return res;
}

bool DBMySQL::next()
{
    return res->next();
}

int DBMySQL::getInt(int ind)
{
    return res->getInt(ind);
}

int DBMySQL::getRow()
{
    return res->getRow();
}

sql::SQLString DBMySQL::getString(std::string& colLabel)
{
    return res->getString(colLabel);
}
