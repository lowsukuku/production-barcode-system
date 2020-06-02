#include "ScanerMapper.h"


ScanerMapper::ScanerMapper(void *dataBase) {

}

err_code ScanerMapper::signInScaner(DeviceScaner &scaner) {
    return WRONG_LOGIN;
}

err_code ScanerMapper::signUpScaner(DeviceScaner &scaner) {
    return WRONG_LOGIN;
}

void *ScanerMapper::deleteScaner(DeviceScaner &scaner) {
    return nullptr;
}
