#include "controllerfordatabase.h"

ControllerForDataBase::ControllerForDataBase()
{

}

bool ControllerForDataBase::isAuthorized(const QString &login, const QString &password)
{
    return true;
}

bool ControllerForDataBase::addProductType(const QString &name)
{
    return true;
}

bool ControllerForDataBase::addProduct(const QString &productType, const QString &id)
{
    return true;
}

QStringList ControllerForDataBase::getProduct(const QString &productType, const QString &id)
{
    return {};
}

QStringList ControllerForDataBase::getProductsByType(const QString &productType)
{
    return {};
}

QStringList ControllerForDataBase::getAllProductsType()
{
    return {};
}

QStringList ControllerForDataBase::getInfoForProductType(const QString &productType)
{
    return {};
}
