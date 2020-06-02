#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace sql;
int main(void)
{
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet  *res;

    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306","newuser","123456789Qqw_!");

    stmt = con->createStatement();
//    stmt->execute("CREATE DATABASE Scaner");
    stmt->execute("USE Scaner");
    stmt->execute("DROP TABLE IF EXISTS test");
    stmt->execute("CREATE TABLE devices(id INT AUTO_INCREMENT PRIMARY KEY,"
                  "model_name varchar(100),"
                  "deviceId BIGINT UNSIGNED,"
                  "creationUtc INT UNSIGNED,"
                  "mountingUtc INT UNSIGNED,"
                  "tuningUtc INT UNSIGNED,"
                  "quailityCheckUtc INT UNSIGNED,"
                  "shipmentUtc INT UNSIGNED,"
                  "mountingPassed BOOL,"
                  "tuningPassed BOOL,"
                  "qualityCheckPassed BOOL,"
                  "shipmentPassed BOOL)");
    stmt->execute("CREATE TABLE users(id INT AUTO_INCREMENT PRIMARY KEY,"
                  "name varchar(45) ,"
                  "surname varchar(45) ,"
                  "role varchar(45))");
    stmt->execute("INSERT INTO users(name, surname, role) "
                  "VALUES "
                  "('ivan', 'petrovich', 'member')");
    stmt->execute("CREATE TABLE models(id INT AUTO_INCREMENT PRIMARY KEY,"
                  "modelname varchar(100),"
                  "creationUTC BIGINT UNSIGNED,"
                  "amount BIGINT UNSIGNED,"
                  "amountOfMountedProduct BIGINT UNSIGNED,"
                  "amountOfTuningProduct BIGINT UNSIGNED,"
                  "amountOfQualityCheckProduct BIGINT UNSIGNED,"
                  "amountOfShipmentProduct BIGINT UNSIGNED)");
    stmt->execute("INSERT INTO models( modelname,creationUTC, amount, amountOfMountedProduct, "
                  "amountOfTuningProduct, amountOfQualityCheckProduct, amountOfShipmentProduct) "
                  "VALUES "
                  "(\"kek\",1,2,3,4,5,6)");

    res = stmt->executeQuery("SELECT * FROM models ORDER BY id ASC");
    while (res->next()) {
        // You can use either numeric offsets...
        std::cout << "id = " << res->getInt(2); // getInt(1) returns the first column
        // ... or column names for accessing results.
        // The latter is recommended.
    }

    delete res;
    delete stmt;
    delete con;

    return 0;
}