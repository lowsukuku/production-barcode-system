#ifndef CONTROLLERFORDATABASE_H
#define CONTROLLERFORDATABASE_H

#include <QObject>
#include <structuresForTable.h>
#include <boost/property_tree/ptree.hpp>


class ControllerForDataBase: public QObject
{
    Q_OBJECT
public:
    ControllerForDataBase();
    bool isAuthorized(const QString& login, const QString& password);//
    bool addProductType(const QString& name);//
    QStringList addProduct(const QString& productType, const QString& amount);//
    ProductHistory getProductHistory(const QString& productType, const QString& id);//
    QList<Product> getProductsByType(const QString& productType);//
    QList<ProductType> getAllProductsType();//
    QStringList getIdByType(const QString& productType);
    QStringList getTypesList();//
    QList<Product> getAllProducts();//
    ~ControllerForDataBase(){}
private:
    boost::property_tree::ptree sendGetRequest(std::string target);
    boost::property_tree::ptree sendPostRequest(std::string target, std::string json_body);
    std::string userLogin, userPassword;
};

#endif // CONTROLLERFORDATABASE_H
