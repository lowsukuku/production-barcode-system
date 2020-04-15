#include "producttab.h"

ProductTab::ProductTab( QWidget *parent) : QWidget(parent)
{

    productTypes.addItems({"T1","T2", "T3"});
    productIds.addItems({"0","1","2"});
    printBareCodeBtn.setText("Печать");
    saveBareCodeInFileBtn.setText("Сохранить в файл");

    productTable.setColumnCount(3);
    productTable.setHorizontalHeaderLabels({"Зав. номер", "Дата добавления", "Состояние"});
    productTable.setSortingEnabled(true);
    productTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0; i<5; i++){
        productTable.insertRow(i);
        for(int j=0; j< 7; j++)
        productTable.setItem(i,j, new QTableWidgetItem("col"+QString::number(i)+" "+ QString::number(j)));
    }
    productTable.resizeColumnsToContents();
    productTable.resizeRowsToContents();

    layout.addWidget(&productTypes);
    layout.addWidget(&productIds);
    layout.addWidget(&printBareCodeBtn);
    layout.addWidget(&saveBareCodeInFileBtn);
    layout.addWidget(&productTable);
    setLayout(&layout);

    connect(&printBareCodeBtn, SIGNAL(clicked()), this, SLOT(onClickedPrintBareCode()));
    connect(&saveBareCodeInFileBtn, SIGNAL(clicked()), this, SLOT(onClickedSaveBareCodeInFile()));

}

void ProductTab::updateTableData(const QStringList data){
    for(auto i:data){
        qDebug()<<i;
    }
}

void ProductTab::updateProductTypes(const QStringList productTypes){
    for(auto i:productTypes){
        qDebug()<<i;
    }
}

void ProductTab::updateIds(const QStringList idList){
    for(auto i:idList){
        qDebug()<<i;
    }
}


//void  needPrintBarecode(const QList<QImage>& img);
//void needSaveBarecode(const QList<QImage>& img);

void ProductTab::onClickedPrintBareCode()
{
    qDebug()<<"onClickedPrintBareCode\n";
    emit needPrintBarecode({});
}

void ProductTab::onClickedSaveBareCodeInFile()
{
     qDebug()<<"onClickedSaveBareCodeInFile\n";
    emit needSaveBarecode({});
}
