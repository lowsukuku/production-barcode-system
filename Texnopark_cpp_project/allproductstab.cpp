#include "allproductstab.h"

AllProductsTab::AllProductsTab(QWidget *parent) : QWidget(parent)
{
    productsTable.setColumnCount(4);
    productsTable.setHorizontalHeaderLabels({"Модель", "Дата добавления", "Зав. номер", "Состояние"});
    productsTable.setSortingEnabled(true);
    productsTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0; i<5; i++){
        productsTable.insertRow(i);
        for(int j=0; j< 4; j++)
        productsTable.setItem(i,j, new QTableWidgetItem("col"+QString::number(i)+" "+ QString::number(j)));
    }
    productsTable.resizeColumnsToContents();
    productsTable.resizeRowsToContents();
    layout.addWidget(&productsTable);
    setLayout(&layout);
}



void AllProductsTab::updateTableData(const QStringList data){
    for(auto i:data){
        qDebug()<<i;
    }
}
