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
    stmt->execute("CREATE DATABASE Scaner");
    stmt->execute("USE Scaner");
    stmt->execute("DROP TABLE IF EXISTS test");
    stmt->execute("CREATE TABLE test(id INT AUTO_INCREMENT PRIMARY KEY,"
                  "deviceId BIGINT UNSIGNED,"
                  "modelId INT UNSIGNED,"
                  "creationUtc INT UNSIGNED,"
                  "serialNumber INT UNSIGNED,"
                  "mountingUtc INT UNSIGNED,"
                  "tuningUtc INT UNSIGNED,"
                  "quailityCheckUtc INT UNSIGNED,"
                  "shipmentUtc INT UNSIGNED,"
                  "mountingPassed BOOL,"
                  "tuningPassed BOOL,"
                  "qualityCheckPassed BOOL,"
                  "shipmentPassed BOOL)");
    stmt->execute("INSERT INTO test(deviceId, modelId, creationUtc,"
                  "serialNumber, mountingUtc, tuningUtc,"
                  "quailityCheckUtc, shipmentUtc, mountingPassed,"
                  "tuningPassed, qualityCheckPassed, shipmentPassed)"
                  "VALUES"
                  "(1234,0,0,0,0,0,0,0,0,0,0,0)");

    res = stmt->executeQuery("SELECT * FROM test ORDER BY id ASC");
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