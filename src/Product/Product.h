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

    void setDeviceId(ULLInt_t deviceId);
    ULLInt_t getDeviceId();

    void setModelId(ULInt_t modelId);
    ULInt_t getModelId();

    void setCreationUtc(ULInt_t creationUtc);
    ULInt_t getCreationUtc();

    void setSerialNumber(ULInt_t serialNumber);
    ULInt_t getSerialNumber();

    void setMountingUtc(ULInt_t mountingUtc);
    ULInt_t getMountingUtc();

    void setTuningUtc(ULInt_t tuningUtc);
    ULInt_t getTuningUtc();

    void setQuailityCheckUtc(ULInt_t quailityCheckUtc);
    ULInt_t getQuailityCheckUtc();

    void setShipmentUtc(ULInt_t shipmentUtc);
    ULInt_t getShipmentUtc();

    void setMountingPassed(bool mountingPassed);
    bool getMountingPassed();

    void setTuningPassed(bool tuningPassed);
    bool getTuningPassed();

    void setQualityCheckPassed(bool qualityCheckPassed);
    bool getQualityCheckPassed();

    void setShipmentPassed(bool shipmentPassed);
    bool getShipmentPassed();
};


#endif //DB_PRODUCT_H
