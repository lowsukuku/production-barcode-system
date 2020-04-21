#ifndef ALLPRODUCTSTAB_H
#define ALLPRODUCTSTAB_H

#include <QtWidgets>

class AllProductsTab : public QWidget
{
    Q_OBJECT
public:
    explicit AllProductsTab(QWidget *parent = nullptr);

    void updateTableData(const QStringList data);
    QTableWidget* getProductsTable(){return &productsTable;}
    ~AllProductsTab(){}

private:
    QVBoxLayout layout;
    QTableWidget productsTable;

};

#endif // ALLPRODUCTSTAB_H
