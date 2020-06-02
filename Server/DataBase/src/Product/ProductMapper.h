#ifndef DB_PRODUCTMAPPER_H
#define DB_PRODUCTMAPPER_H


using namespace std;
#include <vector>
#include "Product.h"
#include "../err_code.h"
#include "../MySQL/MySQL.h"

class ProductMapper {
private:
    DBMySQL *mydb;
    enum productFields {modelId, deviceId};

public:
    explicit ProductMapper();

    err_code addProduct(uint64_t id, std::string &modelName);

    std::string getProductByDeviceId(ULLInt_t deviceId, std::string &modelName);

    bool deleteProductByDeviceId(uint64_t id);

    std::string addModel(const std::string& modelName);

    std::string removeModel(const std::string & modelName);

    std::string getModels();

    std::string modelsToJson(std::vector<std::string> &v);

    std::string checkID(uint64_t id, const std::string& modelName);

    std::string getModelsDet();

    std::string getAllDevices();

    std::string getDevicesByModel(std::string &model);

    std::string getDevicesIdByModel(std::string &model);
};


#endif //DB_PRODUCTMAPPER_H
