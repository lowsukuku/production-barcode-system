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
    vector<Product> getAllProductByModelId(ULInt_t modelId);
    vector<Product> getProductsSortedBy(int firstN, enum productFields field);
    vector<Product> getAllProductsSortedBy(enum productFields field);
    ULLInt_t generateUnicDeviceId();

    bool deleteProductByDeviceId(uint64_t id);

    void addModel(const std::string& modelName);

    void removeModel(const std::string & modelName);

    std::string getModels(const std::string & modelName);
};


#endif //DB_PRODUCTMAPPER_H
