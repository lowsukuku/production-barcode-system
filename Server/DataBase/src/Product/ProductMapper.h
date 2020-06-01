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

    err_code addProduct(Product &product);

    Product getProductByDeviceId(ULLInt_t deviceId);

    bool deleteProductByDeviceId(uint64_t id);

    std::string addModel(const std::string& modelName);

    void removeModel(const std::string & modelName);

    std::string getModels();

    std::string modelsToJson(std::vector<std::string> &v);
};


#endif //DB_PRODUCTMAPPER_H
