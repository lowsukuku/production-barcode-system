#ifndef DB_IGET_H
#define DB_IGET_H


#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../Product/Product.h"
#include "../Product/ProductMapper.h"

namespace pt = boost::property_tree;

class IGet : private ProductMapper
{
public:
    explicit IGet();

    std::string getJsonProductByDeviceId(ULLInt_t deviceId);

    std::string ProductToJson(Product& prod);

    std::string getAllModels();

};


#endif //DB_IGET_H
