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

    mydb->execute(insertQuery);

    return WRONG_LOGIN;
}

void *ProductMapper::deleteProduct(Product &product) {
    return nullptr;
}

Product ProductMapper::getProductByDeviceId(ULLInt_t deviceId) {
    return Product();
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
