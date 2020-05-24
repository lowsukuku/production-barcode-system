#ifndef ALLPRODUCTSTAB_H
#define ALLPRODUCTSTAB_H

#include <QtWidgets>
#include <structuresForTable.h>

class AllProductsTab : public QWidget
{
    Q_OBJECT
public:
    explicit AllProductsTab(QWidget *parent = nullptr);
    void updateTableData(const QList<Product> data);
    QTableWidget* getProductsTable(){return &productsTable;}
    ~AllProductsTab(){}

private:
    QVBoxLayout layout;
    QTableWidget productsTable;

};

#endif // ALLPRODUCTSTAB_H
