#include "IPost.h"

#include <utility>

IPost::IPost() : ProductMapper()
{

}

bool IPost::addToDB(uint64_t id, std::string &modelName)
{
    return this->addProduct(id, modelName) == OK;
}

Product IPost::jsonToProduct(const std::string& sJson)
{
    Product prod;
    // Create a root
    pt::ptree root;

    // Load the json file in this ptree
    std::stringstream JsonSS;
    JsonSS << sJson;

    pt::read_json(JsonSS, root);

    std::string msg = root.get<std::string>("context.deviceId");

    prod.setDeviceId(root.get<ULLInt_t>("context.deviceId"));
    prod.setModelId(root.get<ULInt_t>("context.modelId"));
    prod.setCreationUtc(root.get<ULInt_t>("context.creationUtc"));
    prod.setSerialNumber(root.get<ULInt_t>("context.serialNumber"));
    prod.setMountingUtc(root.get<ULInt_t>("context.mountingUtc"));
    prod.setTuningUtc(root.get<ULInt_t>("context.tuningUtc"));
    prod.setQuailityCheckUtc(root.get<ULInt_t>("context.tuningUtc"));
    prod.setShipmentUtc(root.get<ULInt_t>("context.shipmentUtc"));
    prod.setMountingPassed(root.get<bool>("context.mountingPassed"));
    prod.setTuningPassed(root.get<bool>("context.tuningPassed"));
    prod.setQualityCheckPassed(root.get<bool>("context.qualityCheckPassed"));
    prod.setShipmentPassed(root.get<bool>("context.shipmentPassed"));

    return prod;
}

std::string IPost::removeProduct(uint64_t id) {
    if(!this->deleteProductByDeviceId(id))return "OBJECT_DOES_NOT_EXIST_ERROR";
    return "OK";
}

std::string IPost::addMod(std::string modelName) {
    return this->addModel(std::move(modelName));
}

std::string IPost::removeMod(std::string modelName) {
    return this->removeModel(std::move(modelName));
}

std::string IPost::signIn(string &username, string &password) {
    User u;
    u.setLogin(username);
    u.setPassword(password);
    UserMapper maper;
    return maper.signInUser(u);
}

std::string IPost::checkProductID(uint64_t id, std::string modelName) {
    return checkID(id, modelName);
}
