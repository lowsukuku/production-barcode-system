#ifndef PRODUCTSBYTYPESTAB_H
#define PRODUCTSBYTYPESTAB_H

#include <QtWidgets>

class ProductsByTypesTab : public QWidget
{
    Q_OBJECT
public:
    explicit ProductsByTypesTab(QWidget *parent = nullptr);

    void updateTableData(const QStringList data);
    void updateProductTypes(const QStringList productTypes);
    QComboBox* getProductTypesComboBox(){return & productTypes;}
    QTableWidget* getProductsTable(){ return &productsTable;}
    ~ProductsByTypesTab(){}
private:
    QVBoxLayout layout;
    QTableWidget productsTable;
    QComboBox productTypes;
};

#endif // PRODUCTSBYTYPESTAB_H
