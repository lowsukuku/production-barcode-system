#ifndef DB_SCANERMAPPER_H
#define DB_SCANERMAPPER_H


#include "DeviceScaner.h"
#include "../err_code.h"


class ScanerMapper {
private:
    void *dataBase; // обьект базы данных TO DO поменять тип

public:
    explicit ScanerMapper(void *dataBase);

    err_code signInScaner(DeviceScaner &scaner);
    err_code signUpScaner(DeviceScaner &scaner);

    void *deleteScaner(DeviceScaner &scaner);
};


#endif //DB_SCANERMAPPER_H
