#include "producttypestab.h"

ProductTypesTab::ProductTypesTab(QWidget *parent) : QWidget(parent)
{ 
    productTypesTable.setColumnCount(7);
    productTypesTable.setHorizontalHeaderLabels({"Модель", "Дата добавления", "Всего", "Собрано", "Настроено", "Прошло ОТК", "Отгружено"});
    productTypesTable.setSortingEnabled(true);
    productTypesTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0; i<5; i++){
        productTypesTable.insertRow(i);
        for(int j=0; j< 7; j++)
       // productTypesTable.setItem(i,j, new QTableWidgetItem("col"+QString::number(i)+" "+ QString::number(j)));
        productTypesTable.setCellWidget(i,j, new QLabel("col"+QString::number(i)+" "+ QString::number(j)));
    }
    productTypesTable.resizeColumnsToContents();
    productTypesTable.resizeRowsToContents();
    layout.addWidget(&productTypesTable);
    setLayout(&layout);
}

void ProductTypesTab::updateTableData(const QStringList data){
    for(auto i:data){
        qDebug()<<i;
    }
}
