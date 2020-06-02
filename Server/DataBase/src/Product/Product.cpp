#include "Product.h"


Product::Product() : deviceId(0), modelId(0), creationUtc(0),
                    serialNumber(0), mountingUtc(0), tuningUtc(0),
                    quailityCheckUtc(0), shipmentUtc(0),
                    mountingPassed(false), tuningPassed(false),
                    qualityCheckPassed(false), shipmentPassed(false) {

}

const void Product::setDeviceId(ULLInt_t deviceId) {
    this->deviceId = deviceId;
}

ULLInt_t Product::getDeviceId() {
    return deviceId;
}

const void Product::setModelId(ULInt_t modelId) {
    this->modelId = modelId;
}

ULInt_t Product::getModelId() {
    return modelId;
}

const void Product::setCreationUtc(ULInt_t creationUtc) {
    this->creationUtc = creationUtc;
}

ULInt_t Product::getCreationUtc() {
    return creationUtc;
}

const void Product::setSerialNumber(ULInt_t serialNumber) {
    this->serialNumber = serialNumber;
}

ULInt_t Product::getSerialNumber() {
    return serialNumber;
}

const void Product::setMountingUtc(ULInt_t mountingUtc) {
    this->mountingUtc = mountingUtc;
}

ULInt_t Product::getMountingUtc() {
    return mountingUtc;
}

const void Product::setTuningUtc(ULInt_t tuningUtc) {
    this->tuningUtc = tuningUtc;
}

ULInt_t Product::getTuningUtc() {
    return tuningUtc;
}

const void Product::setQuailityCheckUtc(ULInt_t quailityCheckUtc) {
    this->quailityCheckUtc = quailityCheckUtc;
}

ULInt_t Product::getQuailityCheckUtc() {
    return quailityCheckUtc;
}

const void Product::setShipmentUtc(ULInt_t shipmentUtc) {
    this->shipmentUtc = shipmentUtc;
}

ULInt_t Product::getShipmentUtc() {
    return shipmentUtc;
}

const void Product::setMountingPassed(bool mountingPassed) {
    this->mountingPassed = mountingPassed;
}

bool Product::getMountingPassed() {
    return mountingPassed;
}

const void Product::setTuningPassed(bool tuningPassed) {
    this->tuningPassed = tuningPassed;
}

bool Product::getTuningPassed() {
    return tuningPassed;
}

const void Product::setQualityCheckPassed(bool qualityCheckPassed) {
    this->qualityCheckPassed = qualityCheckPassed;
}

bool Product::getQualityCheckPassed() {
    return qualityCheckPassed;
}

const void Product::setShipmentPassed(bool shipmentPassed) {
    this->shipmentPassed = shipmentPassed;
}

bool Product::getShipmentPassed() {
    return shipmentPassed;
}
