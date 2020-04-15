#include "UserProductMapper.h"


UserProductMapper::UserProductMapper(void *dataBase) {

}

err_code UserProductMapper::update(Product &product) {
    return WRONG_LOGIN;
}

void *UserProductMapper::deleteProduct(Product &product) {
    return nullptr;
}

Product UserProductMapper::getProductByDeviceId(ULLInt_t deviceId) {
    return Product();
}

vector<Product> UserProductMapper::getAllProductByModelId(ULInt_t modelId) {
    return vector<Product>();
}

vector<Product> UserProductMapper::getProductsSortedBy(int firstN, UserProductMapper::productFields field) {
    return vector<Product>();
}

vector<Product> UserProductMapper::getAllProductsSortedBy(UserProductMapper::productFields field) {
    return vector<Product>();
}

ULLInt_t UserProductMapper::generateUnicDeviceId() {
    return 0;
}
