#ifndef DB_SCANERMAPPER_H
#define DB_SCANERMAPPER_H


#include "Scaner.h"
#include "../../err_code.h"


class ScanerMapper {
private:
    void *dataBase; // обьект базы данных TO DO поменять тип

public:
    explicit ScanerMapper(void *dataBase);

    err_code signInScaner(Scaner &scaner);
    err_code signUpScaner(Scaner &scaner);

    void *deleteScaner(Scaner &scaner);
};


#endif //DB_SCANERMAPPER_H
