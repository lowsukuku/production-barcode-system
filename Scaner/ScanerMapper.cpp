#include "ScanerMapper.h"


ScanerMapper::ScanerMapper(void *dataBase) {

}

err_code ScanerMapper::signInScaner(Scaner &scaner) {
    return WRONG_LOGIN;
}

err_code ScanerMapper::signUpScaner(Scaner &scaner) {
    return WRONG_LOGIN;
}

void *ScanerMapper::deleteScaner(Scaner &scaner) {
    return nullptr;
}
