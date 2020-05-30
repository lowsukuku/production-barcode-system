#include "MySQL.h"


DBMySQL::DBMySQL(const char *filename)
{
    driver = get_driver_instance();
    try{
        con = driver->connect("tcp://127.0.0.1:3306","newuser","123456789Qqw_!");

        stmt = con->createStatement();
        stmt->execute("USE Scaner");
    } catch ( std::exception &e ) {
        std::cerr<<"DATABASE_CONNECTION_ERROR: "<<e.what()<<std::endl;
    }
}

DBMySQL::~DBMySQL()
{
    delete res;
    delete stmt;
    delete con;
}

bool DBMySQL::execute(std::string& query)
{
    try {
        sql::SQLString q(query);
        bool flag=stmt->execute(q);
    } catch (std::exception e) {
        std::cerr<<"Error: "<<e.what()<<std::endl;
        return false;
    }
    return true;
}

sql::ResultSet* DBMySQL::executeQuery(std::string& query)
{
    const sql::SQLString q(query);
    res = stmt->executeQuery(q);
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
