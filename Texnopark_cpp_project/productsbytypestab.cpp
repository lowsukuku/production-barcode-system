#include "productsbytypestab.h"

ProductsByTypesTab::ProductsByTypesTab(QWidget *parent) : QWidget(parent)
{
    productTypes.addItems({"T1","T2", "T3"});

    productsTable.setColumnCount(3);
    productsTable.setHorizontalHeaderLabels({"Зав. номер", "Дата добавления", "Состояние"});
    productsTable.setSortingEnabled(true);
    productsTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0; i<5; i++){
        productsTable.insertRow(i);
        for(int j=0; j< 7; j++)
        productsTable.setItem(i,j, new QTableWidgetItem("col"+QString::number(i)+" "+ QString::number(j)));
    }
    productsTable.resizeColumnsToContents();
    productsTable.resizeRowsToContents();

    layout.addWidget(&productTypes);
    layout.addWidget(&productsTable);
    setLayout(&layout);
}


void ProductsByTypesTab::updateTableData(const QStringList data){
    for(auto i:data){
        qDebug()<<i;
    }
}

void ProductsByTypesTab::updateProductTypes(const QStringList productTypes){
    for(auto i:productTypes){
        qDebug()<<i;
    }
}
