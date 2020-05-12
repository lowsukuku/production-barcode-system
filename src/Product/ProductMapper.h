#ifndef DB_PRODUCTMAPPER_H
#define DB_PRODUCTMAPPER_H


using namespace std;
#include <vector>
#include "Product.h"
#include "../../err_code.h"
#include "../MySQL/MySQL.h"

class ProductMapper {
private:
    DBMySQL *mydb;
    enum productFields {modelId, deviceId};

public:
    explicit ProductMapper();

    err_code addProduct(Product &product);
    void *deleteProduct(Product &product);

    Product getProductByDeviceId(ULLInt_t deviceId);
    vector<Product> getAllProductByModelId(ULInt_t modelId);
    vector<Product> getProductsSortedBy(int firstN, enum productFields field);
    vector<Product> getAllProductsSortedBy(enum productFields field);
    ULLInt_t generateUnicDeviceId();
};


#endif //DB_PRODUCTMAPPER_H
