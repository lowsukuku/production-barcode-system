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
    bool flag;
    try {
        sql::SQLString q(query);
        flag=stmt->execute(q);
    } catch (std::exception &e) {
        return false;
    }
    return true;
}

sql::ResultSet* DBMySQL::executeQuery(std::string& query)
{
    try{
        const sql::SQLString q(query);
        res = stmt->executeQuery(query);
    } catch (std::exception &ex) {
        std::cerr<<ex.what()<<std::endl;
    }
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
