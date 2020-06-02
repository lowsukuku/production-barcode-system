#include "IGet.h"


IGet::IGet() : ProductMapper()
{

}

std::string IGet::getJsonProductByDeviceId(ULLInt_t deviceId, std::string &modelName)
{
    return  this->getProductByDeviceId(deviceId, modelName);
}




std::string IGet::ProductToJson(Product &prod)
{
    pt::ptree root;

    root.put("context.deviceId", prod.getDeviceId());
    root.put("context.modelId", prod.getModelId());
    root.put("context.creationUtc", prod.getCreationUtc());
    root.put("context.serialNumber", prod.getSerialNumber());
    root.put("context.mountingUtc", prod.getMountingUtc());
    root.put("context.tuningUtc", prod.getTuningUtc());
    root.put("context.quailityCheckUtc", prod.getQuailityCheckUtc());
    root.put("context.shipmentUtc", prod.getShipmentUtc());
    root.put("context.mountingPassed", prod.getMountingPassed());
    root.put("context.tuningPassed", prod.getTuningPassed());
    root.put("context.qualityCheckPassed", prod.getQualityCheckPassed());
    root.put("context.shipmentPassed", prod.getShipmentPassed());

    std::stringstream JsonSS;
    pt::write_json(JsonSS, root);

    return JsonSS.str();
}

std::string IGet::getAllModels() {
    return this->getModels();
}

std::string IGet::getModDet() {
    return getModelsDet();
}

std::string IGet::AllDevices() {
    return getAllDevices();
}

std::string IGet::deviceByModel(string &model) {
    return getDevicesByModel(model);
}

std::string IGet::deviceIdByModel(string &model) {
    return getDevicesIdByModel(model);
}



