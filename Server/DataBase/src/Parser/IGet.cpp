#include "IGet.h"


IGet::IGet() : ProductMapper()
{

}

std::string IGet::getJsonProductByDeviceId(ULLInt_t deviceId)
{
    auto prod = this->getProductByDeviceId(deviceId);

    return this->ProductToJson(prod);
}

std::string IGet::removeProduct(uint64_t id) {
    if(!this->deleteProductByDeviceId(id))return "OBJECT_DOES_NOT_EXIST_ERROR";
    return "OK";
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




