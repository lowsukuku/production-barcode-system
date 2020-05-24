#ifndef STRUCTURESFORTABLE_H
#define STRUCTURESFORTABLE_H
#include <QString>
struct ProductType{
    QString name;
    QString date;
    QString amount;
    QString amountOfBuildsProduct;
    QString amountOfSettingProduct;
    QString amountAfterOtk;
    QString amountOfShippedProduct;
};

struct Product{
    QString type;
    QString date;
    QString id;
    QString state;
};

struct ProductHistory{
   QString productType;
   QString id;
   QString dateOfAdd;
   QString dateOfBuild;
   QString dateOfAdjustment;
   QString dateOfOtk;
   QString dateOfShipping;
};

#endif // STRUCTURESFORTABLE_H
