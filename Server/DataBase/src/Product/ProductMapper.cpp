#include "ProductMapper.h"
#include <ctime>
#include <cstring>

ProductMapper::ProductMapper() {
    mydb = new DBMySQL();
}


err_code ProductMapper::addProduct(uint64_t id, std::string &modelName) {
    const time_t timer = time(NULL);
    localtime(&timer);
    std::string data = "'" + modelName + "', " + std::to_string(id) + "," + std::to_string(timer) + ",0,0,0,0,0,0,0,0";

    std::string insertQuery = "INSERT INTO devices(model_name, deviceId,  creationUtc,"
                              " mountingUtc, tuningUtc,"
                              "quailityCheckUtc, shipmentUtc, mountingPassed,"
                              "tuningPassed, qualityCheckPassed, shipmentPassed)"
                              "VALUES (" + data + ")";

    mydb->execute(insertQuery);

//    update  models set amount =amount+1 where id=7;
    std::string command = "UPDATE models SET amount = amount+1 WHERE modelname = '" + modelName + "'";
    mydb->execute(command);

    return OK;
}

std::string ProductMapper::addModel(const std::string &modelName) {
    std::string query = "CREATE TABLE " + modelName + " (id INT AUTO_INCREMENT PRIMARY KEY)";
    if (!mydb->execute(query))return "TABLE_EXIST_ERROR";
    const time_t timer = time(NULL);
    localtime(&timer);
    query = "INSERT INTO models (modelname,creationUTC,  amount,  amountOfMountedProduct, amountOfTuningProduct, amountOfQualityCheckProduct, amountOfShipmentProduct)"
            "VALUES (\"" + modelName + "\", " + std::to_string(timer) + ", 0, 0, 0, 0, 0)";
    mydb->execute(query);
    return "OK";
}

std::string ProductMapper::removeModel(const string &modelName) {
    std::string query = "DROP TABLE " + modelName;
    if (!mydb->execute(query)) return "TABLE_DOES_NOT_EXIST_ERROR";

    query = "DELETE FROM models WHERE modelname = '" + modelName + "'";
    mydb->execute(query);
    return "OK";
}

bool ProductMapper::deleteProductByDeviceId(uint64_t id) {
    std::string query = "DELETE FROM test WHERE deviceId=" + std::to_string(id);
    return mydb->execute(query);
}

std::string ProductMapper::getProductByDeviceId(ULLInt_t deviceId, std::string &modelName) {
    std::string query =
            "SELECT * FROM devices WHERE deviceId=" + std::to_string(deviceId) + " AND model_name = '" + modelName +
            "'";
    mydb->executeQuery(query);
    mydb->next();
    std::string s, json;

    s = "model_name";
    json += '{';
    json += "modelname : '";
    uint16_t checker = json.size();
    try {
        json += mydb->getString(s) + "', ";
    } catch (std::exception &ex) {
        return "DEVICE_NOT_FOUND_ERROR";
    }

    if (json.size() == checker)
        return "DEVICE_NOT_FOUND_ERROR";
    json += "creationUtc : '";
    json += std::to_string(mydb->getInt(3)) + ", ";
    json += "amount : '";
    json += std::to_string(mydb->getInt(4)) + ", ";
    json += "amountOfMountedProduct : '";
    json += std::to_string(mydb->getInt(5)) + ", ";
    json += "amountOfMountedProduct : '";
    json += std::to_string(mydb->getInt(5)) + ", ";
    json += "amountOfQualityCheckProduct : '";
    json += std::to_string(mydb->getInt(6)) + ", ";
    json += "amountOfShipmentProduct : '";
    json += std::to_string(mydb->getInt(7)) + ", ";
    json += "}";


    return json;
}

std::string ProductMapper::getModels() {
    std::string query = "SELECT * FROM models";
    mydb->executeQuery(query);
    std::vector<std::string> v;
    std::string s = "modelname";

    while (mydb->next()) {
        v.push_back(mydb->getString(s));
    }
    return modelsToJson(v);
}

std::string ProductMapper::modelsToJson(std::vector<std::string> &v) {
    std::string json;
    json += "{[";
    for (const auto &model:v) {
        json += model + ',';
    }
    json += "]}";
    return json;
}

//select * from devices where deviceid=1 and model_name = 'model_1';
std::string ProductMapper::checkID(uint64_t id, const std::string &modelName) {
    std::string command =
            "SELECT * FROM devices WHERE deviceid = " + std::to_string(id) + " and model_name = '" + modelName + "'";
    mydb->executeQuery(command);
    std::string checker;

    std::string s = "model_name";
    mydb->next();
    try {
        checker = mydb->getString(s);
    } catch (std::exception &ex) {
        return "OK";
    }
    return "FOUND";
}

std::string ProductMapper::getModelsDet() {

    std::string command = "SELECT * FROM models";
    mydb->executeQuery(command);

    std::string json = "[";
    std::string s;
    while (mydb->next()) {
        json += "{";
        s = "modelname";
        json += "modelname : '";
        json += mydb->getString(s) + "', ";
        json += "creationUtc : '";
        json += std::to_string(mydb->getInt(3)) + ", ";
        json += "amount : '";
        json += std::to_string(mydb->getInt(4)) + ", ";
        json += "amountOfMountedProduct : '";
        json += std::to_string(mydb->getInt(5)) + ", ";
        json += "amountOfMountedProduct : '";
        json += std::to_string(mydb->getInt(5)) + ", ";
        json += "amountOfQualityCheckProduct : '";
        json += std::to_string(mydb->getInt(6)) + ", ";
        json += "amountOfShipmentProduct : '";
        json += std::to_string(mydb->getInt(7)) + ", ";
        json += "}, ";
    }
    json += "]";
    return json;
}

std::string ProductMapper::getAllDevices() {
    std::string command = "SELECT * FROM devices";
    mydb->executeQuery(command);
    std::string json = "[";
    std::string s;
    while (mydb->next()) {
        json += "{";
        s = "model_name";
        json += "model_name : '";
        json += mydb->getString(s) + "', ";
        json += "deviceId : '";
        json += std::to_string(mydb->getInt(3)) + ", ";
        json += "creationUtc : '";
        json += std::to_string(mydb->getInt(4)) + ", ";
        json += "tuningUtc : '";
        json += std::to_string(mydb->getInt(5)) + ", ";
        json += "quailityCheckUtc : '";
        json += std::to_string(mydb->getInt(5)) + ", ";
        json += "shipmentUtc : '";
        json += std::to_string(mydb->getInt(6)) + ", ";
        json += "mountingPassed : '";
        json += std::to_string(mydb->getInt(7)) + ", ";
        json += "tuningPassed : '";
        json += std::to_string(mydb->getInt(8)) + ", ";
        json += "qualityCheckPassed : '";
        json += std::to_string(mydb->getInt(9)) + ", ";
        json += "shipmentPassed : '";
        json += std::to_string(mydb->getInt(10)) + ", ";
        json += "}, ";
    }
    json += "]";
    return json;
}

std::string ProductMapper::getDevicesByModel(std::string &model) {
//    select * from devices where model_name='model_1';

    std::string comand = "SELECT * FROM devices WHERE model_name = '" + model + "'";
    mydb->executeQuery(comand);


    std::string json = "[";

    std::string s;
    while (mydb->next()) {
        json += "{";
        s = "model_name";
        json += "model_name : '";
        json += mydb->getString(s) + "', ";
        json += "deviceId : '";
        json += std::to_string(mydb->getInt(3)) + ", ";
        json += "creationUtc : '";
        json += std::to_string(mydb->getInt(4)) + ", ";
        json += "tuningUtc : '";
        json += std::to_string(mydb->getInt(5)) + ", ";
        json += "quailityCheckUtc : '";
        json += std::to_string(mydb->getInt(5)) + ", ";
        json += "shipmentUtc : '";
        json += std::to_string(mydb->getInt(6)) + ", ";
        json += "mountingPassed : '";
        json += std::to_string(mydb->getInt(7)) + ", ";
        json += "tuningPassed : '";
        json += std::to_string(mydb->getInt(8)) + ", ";
        json += "qualityCheckPassed : '";
        json += std::to_string(mydb->getInt(9)) + ", ";
        json += "shipmentPassed : '";
        json += std::to_string(mydb->getInt(10)) + ", ";
        json += "}, ";
    }
    json += "]";
    if (json.size() == 2)
        return "MODEL_NOT_FOUND_ERROR";
    return json;
}

std::string ProductMapper::getDevicesIdByModel(string &model) {
    std::string comand = "SELECT * FROM devices WHERE model_name = '" + model + "'";
    mydb->executeQuery(comand);


    std::string json = "[";

    std::string s;
    try{
        while (mydb->next()) {
            json += "{";
            json += "deviceId : '";
            json += std::to_string(mydb->getInt(3)) + ", ";

            json += "},";
        }
    } catch (std::exception &ex) {
            return "MODEL_NOT_FOUND_ERROR";
    }

    json += "]";

    return json;
}
