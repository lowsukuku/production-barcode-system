#ifndef DB_PRODUCT_H
#define DB_PRODUCT_H


typedef unsigned long long int ULLInt_t;
typedef unsigned long int ULInt_t;


class Product {
private:
    ULLInt_t deviceId;
    ULInt_t modelId;
    ULInt_t creationUtc;
    ULInt_t serialNumber;
    ULInt_t mountingUtc;
    ULInt_t tuningUtc;
    ULInt_t quailityCheckUtc;
    ULInt_t shipmentUtc;
    bool mountingPassed;
    bool tuningPassed;
    bool qualityCheckPassed;
    bool shipmentPassed;

public:
    Product();

    const void setDeviceId(ULLInt_t deviceId);
    ULLInt_t getDeviceId();

    const void setModelId(ULInt_t modelId);
    ULInt_t getModelId();

    const void setCreationUtc(ULInt_t creationUtc);
    ULInt_t getCreationUtc();

    const void setSerialNumber(ULInt_t serialNumber);
    ULInt_t getSerialNumber();

    const void setMountingUtc(ULInt_t mountingUtc);
    ULInt_t getMountingUtc();

    const void setTuningUtc(ULInt_t tuningUtc);
    ULInt_t getTuningUtc();

    const void setQuailityCheckUtc(ULInt_t quailityCheckUtc);
    ULInt_t getQuailityCheckUtc();

    const void setShipmentUtc(ULInt_t shipmentUtc);
    ULInt_t getShipmentUtc();

    const void setMountingPassed(bool mountingPassed);
    bool getMountingPassed();

    const void setTuningPassed(bool tuningPassed);
    bool getTuningPassed();

    const void setQualityCheckPassed(bool qualityCheckPassed);
    bool getQualityCheckPassed();

    const void setShipmentPassed(bool shipmentPassed);
    bool getShipmentPassed();
};


#endif //DB_PRODUCT_H
