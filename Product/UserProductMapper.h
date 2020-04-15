#ifndef DB_USERPRODUCTMAPPER_H
#define DB_USERPRODUCTMAPPER_H


using namespace std;
#include <vector>
#include "Product.h"
#include "../err_code.h"


class UserProductMapper {
private:
    void *dataBase; // обьект базы данных TO DO поменять тип
    enum productFields {modelId, deviceId};

public:
    explicit UserProductMapper(void *dataBase);

    err_code update(Product &product);
    void *deleteProduct(Product &product);

    Product getProductByDeviceId(ULLInt_t deviceId);
    vector<Product> getAllProductByModelId(ULInt_t modelId);
    vector<Product> getProductsSortedBy(int firstN, enum productFields field);
    vector<Product> getAllProductsSortedBy(enum productFields field);
    ULLInt_t generateUnicDeviceId();
};


#endif //DB_USERPRODUCTMAPPER_H
