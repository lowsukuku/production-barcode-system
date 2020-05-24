#include "productsbytypestab.h"

ProductsByTypesTab::ProductsByTypesTab(QWidget *parent) : QWidget(parent)
{


    productsTable.setColumnCount(4);
    productsTable.setHorizontalHeaderLabels({"Модель", "Дата добавления", "Зав. номер", "Состояние"});
    productsTable.setSortingEnabled(true);
    productsTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
    productsTable.resizeColumnsToContents();
    productsTable.resizeRowsToContents();

    layout.addWidget(&productTypes);
    layout.addWidget(&productsTable);
    setLayout(&layout);
}


void ProductsByTypesTab::updateTableData(const QList<Product> data){
    qDebug()<<"ProductsByTypesTab updateTableData"<<"\n";
   for(auto i:data){
       qDebug()<<i.id<<"\n";
   }
   productsTable.clear();
   productsTable.setRowCount(0);
   productsTable.setHorizontalHeaderLabels({"Модель", "Дата добавления", "Зав. номер", "Состояние"});
   int i = 0;
   for(auto it = data.begin(); it!=data.end(); it++){
       productsTable.insertRow(i);
       productsTable.setCellWidget(i,0, new QLabel(it->type));
       productsTable.setCellWidget(i,1, new QLabel(it->date));
       productsTable.setCellWidget(i,2, new QLabel(it->id));
       productsTable.setCellWidget(i,3, new QLabel(it->state));
       i++;
   }
   productsTable.resizeColumnsToContents();
   productsTable.resizeRowsToContents();
}

void ProductsByTypesTab::updateProductTypes(const QStringList productTypes){
   this->productTypes.clear();
   this->productTypes.addItems(productTypes);
}

QComboBox *ProductsByTypesTab::getProductTypesComboBox(){return & productTypes;}

QTableWidget *ProductsByTypesTab::getProductsTable(){ return &productsTable;}
