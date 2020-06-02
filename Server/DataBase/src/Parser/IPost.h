#ifndef DB_IPOST_H
#define DB_IPOST_H


#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../Product/Product.h"
#include "../Product/ProductMapper.h"
#include "../User/UserMapper.h"

namespace pt = boost::property_tree;

class IPost : private ProductMapper
{
public:
    explicit IPost();

    bool addToDB(uint64_t id, std::string &modelName);

    Product jsonToProduct(const std::string& sJson);

    std::string removeProduct(uint64_t id);

    std::string addMod(std::string modelName);

    std::string removeMod(std::string modelName);

    std::string signIn(std::string &username, std::string &password);

    std::string checkProductID(uint64_t id, std::string modelName);
};


#endif //DB_IPOST_H
