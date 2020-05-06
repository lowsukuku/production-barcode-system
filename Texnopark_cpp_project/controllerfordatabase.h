#ifndef CONTROLLERFORDATABASE_H
#define CONTROLLERFORDATABASE_H

#include <QObject>
#include <structuresForTable.h>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace http = boost::beast::http;
using boost::property_tree::ptree; using boost::property_tree::read_json; using boost::property_tree::write_json;
using boost::asio::ip::tcp;
class ControllerForDataBase: public QObject
{
    Q_OBJECT
public:
    ControllerForDataBase();
    bool isAuthorized(const QString& login, const QString& password);
    bool addProductType(const QString& name);
    QStringList addProduct(const QString& productType, const QString& amount);
    ProductHistory getProductHistory(const QString& productType, const QString& id);
    QList<Product> getProductsByType(const QString& productType);
    QList<ProductType> getAllProductsType();
    QStringList getIdByType(const QString& productType);
    QStringList getTypesList();
    QList<Product> getAllProducts();
    ~ControllerForDataBase(){}
private:
    ptree sendGetRequest(std::string target);
    ptree sendPostRequest(std::string target, std::string json_body);
    std::string userLogin, userPassword;
};

#endif // CONTROLLERFORDATABASE_H
