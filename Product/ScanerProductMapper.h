#ifndef DB_SCANERPRODUCTMAPPER_H
#define DB_SCANERPRODUCTMAPPER_H


#include "Product.h"
#include "../err_code.h"

class ScanerProductMapper {
private:
    void *dataBase; // обьект базы данных TO DO поменять тип

public:
    explicit ScanerProductMapper(void *dataBase);

    err_code update(Product &product);
};


#endif //DB_SCANERPRODUCTMAPPER_H
