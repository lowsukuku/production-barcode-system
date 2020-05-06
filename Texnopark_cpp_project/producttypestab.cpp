#include "producttypestab.h"

ProductTypesTab::ProductTypesTab(QWidget *parent) : QWidget(parent)
{ 
    productTypesTable.setColumnCount(7);

    productTypesTable.setSortingEnabled(true);
    productTypesTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout.addWidget(&productTypesTable);
    setLayout(&layout);
}

void ProductTypesTab::updateTableData(QList<ProductType> data){
     qDebug()<<"updateTableData"<<"\n";
    for(auto i:data){
        qDebug()<<i.name<<"\n";
    }
    productTypesTable.clear();
    productTypesTable.setRowCount(0);
    productTypesTable.setHorizontalHeaderLabels({"Модель", "Дата добавления", "Всего", "Собрано", "Настроено", "Прошло ОТК", "Отгружено"});
    int i = 0;
    for(auto it = data.begin(); it!=data.end(); it++){
        productTypesTable.insertRow(i);
        productTypesTable.setCellWidget(i,0, new QLabel(it->name));
        productTypesTable.setCellWidget(i,1, new QLabel(it->date));
        productTypesTable.setCellWidget(i,2, new QLabel(it->amount));
        productTypesTable.setCellWidget(i,3, new QLabel(it->amountOfBuildsProduct));
        productTypesTable.setCellWidget(i,4, new QLabel(it->amountOfSettingProduct));
        productTypesTable.setCellWidget(i,5, new QLabel(it->amountAfterOtk));
        productTypesTable.setCellWidget(i,6, new QLabel(it->amountOfShippedProduct));
    }
    productTypesTable.resizeColumnsToContents();
    productTypesTable.resizeRowsToContents();

}
