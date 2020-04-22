#ifndef PRODUCTTYPESTAB_H
#define PRODUCTTYPESTAB_H

#include <QtWidgets>
class ProductTypesTab : public QWidget
{
    Q_OBJECT
public:
    explicit ProductTypesTab(QWidget *parent = nullptr);
    void updateTableData(const QStringList data);
    const QTableWidget* getProductTypeTable(){return &productTypesTable;}
    ~ProductTypesTab(){}

private:
    QVBoxLayout layout;
    QTableWidget productTypesTable;

};

#endif // PRODUCTTYPESTAB_H
