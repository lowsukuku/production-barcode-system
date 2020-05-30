#include "ProductMapper.h"


ProductMapper::ProductMapper() {
    mydb = new DBMySQL();
}


err_code ProductMapper::addProduct(Product &product) {
    std::string data = std::to_string(product.getDeviceId()) + "," +
                     std::to_string(product.getModelId()) + "," +
                     std::to_string(product.getCreationUtc()) + "," +
                     std::to_string(product.getSerialNumber()) + "," +
                     std::to_string(product.getMountingUtc()) + "," +
                     std::to_string(product.getTuningUtc()) + "," +
                     std::to_string(product.getQuailityCheckUtc()) + "," +
                     std::to_string(product.getShipmentUtc()) + "," +
                     std::to_string(product.getMountingPassed()) + "," +
                     std::to_string(product.getTuningPassed()) + "," +
                     std::to_string(product.getQualityCheckPassed()) + "," +
                     std::to_string(product.getShipmentPassed());

    std::string insertQuery = "INSERT INTO test(deviceId, modelId, creationUtc,"
                              "serialNumber, mountingUtc, tuningUtc,"
                              "quailityCheckUtc, shipmentUtc, mountingPassed,"
                              "tuningPassed, qualityCheckPassed, shipmentPassed)"
                              "VALUES (" + data + ")";

    if(mydb->execute(insertQuery))return OK;

    return WRONG_LOGIN;
}

void *ProductMapper::deleteProduct(Product &product) {
    return nullptr;
}

Product ProductMapper::getProductByDeviceId(ULLInt_t deviceId)
{
    std::string query = "SELECT * FROM test WHERE deviceId=" + std::to_string(deviceId);
    mydb->executeQuery(query);
    mydb->next();

    Product prod;
    prod.setDeviceId(mydb->getInt(2));
    prod.setModelId(mydb->getInt(3));
    prod.setCreationUtc(mydb->getInt(4));
    prod.setSerialNumber(mydb->getInt(5));
    prod.setMountingUtc(mydb->getInt(6));
    prod.setTuningUtc(mydb->getInt(7));
    prod.setQuailityCheckUtc(mydb->getInt(8));
    prod.setShipmentUtc(mydb->getInt(9));
    prod.setMountingPassed(mydb->getInt(10));
    prod.setTuningPassed(mydb->getInt(11));
    prod.setQualityCheckPassed(mydb->getInt(12));
    prod.setShipmentPassed(mydb->getInt(13));

    return prod;
}

vector<Product> ProductMapper::getAllProductByModelId(ULInt_t modelId) {
    return vector<Product>();
}

vector<Product> ProductMapper::getProductsSortedBy(int firstN, ProductMapper::productFields field) {
    return vector<Product>();
}

vector<Product> ProductMapper::getAllProductsSortedBy(ProductMapper::productFields field) {
    return vector<Product>();
}

ULLInt_t ProductMapper::generateUnicDeviceId() {
    return 0;
}
