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
    int getDeviceId();

    void setModelId(ULInt_t modelId);
    int getModelId();

    void setCreationUtc(ULInt_t creationUtc);
    int getCreationUtc();

    void setSerialNumber(ULInt_t serialNumber);
    int getSerialNumber();

    void setMountingUtc(ULInt_t mountingUtc);
    int getMountingUtc();

    void setTuningUtc(ULInt_t tuningUtc);
    int getTuningUtc();

    void setQuailityCheckUtc(ULInt_t quailityCheckUtc);
    int getQuailityCheckUtc();

    void setShipmentUtc(ULInt_t shipmentUtc);
    int getShipmentUtc();

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
