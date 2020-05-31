#ifndef DB_IPOST_H
#define DB_IPOST_H


#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../Product/Product.h"
#include "../Product/ProductMapper.h"

namespace pt = boost::property_tree;

class IPost : private ProductMapper
{
public:
    explicit IPost();

    bool addToDB(const std::string& sJson);

    Product jsonToProduct(const std::string& sJson);

    std::string removeProduct(uint64_t id);

    void addMod(std::string modelName);

    void removeMod(std::string modelName);
};


#endif //DB_IPOST_H
