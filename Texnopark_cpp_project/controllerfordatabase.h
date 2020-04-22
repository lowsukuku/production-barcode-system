#ifndef CONTROLLERFORDATABASE_H
#define CONTROLLERFORDATABASE_H

#include <QObject>

class ControllerForDataBase: public QObject
{
    Q_OBJECT
public:
    ControllerForDataBase();
    bool isAuthorized(const QString& login, const QString& password);
    bool addProductType(const QString& name);
    bool addProduct(const QString& productType, const QString& id);
    QStringList getProduct(const QString& productType, const QString& id);
    QStringList getProductsByType(const QString& productType);
    QStringList getAllProductsType();
    QStringList getInfoForProductType(const QString& productType);
    ~ControllerForDataBase(){}


};

#endif // CONTROLLERFORDATABASE_H
