#include "producttab.h"

ProductTab::ProductTab( QWidget *parent) : QWidget(parent)
{

    printBareCodeBtn.setText("Печать");
    saveBareCodeInFileBtn.setText("Сохранить в файл");
    productTable.setColumnCount(4);
    productTable.setHorizontalHeaderLabels({"Модель","Номер","Дата", "Событие"});
    productTable.setSortingEnabled(true);
    productTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout.addWidget(&productTypes);
    layout.addWidget(&productIds);
    layout.addWidget(&barecodeImgLabel);
    layout.addWidget(&printBareCodeBtn);
    layout.addWidget(&saveBareCodeInFileBtn);
    layout.addWidget(&productTable);
    setLayout(&layout);

    connect(&printBareCodeBtn, SIGNAL(clicked()), this, SLOT(onClickedPrintBareCode()));
    connect(&saveBareCodeInFileBtn, SIGNAL(clicked()), this, SLOT(onClickedSaveBareCodeInFile()));

}

void ProductTab::updateTableDateAndBarecode(const ProductHistory& data, const QImage& barecode){
    qDebug()<<data.productType<<" "<<data.id<<"\n";
    barecodeImgLabel.setPixmap(QPixmap::fromImage(barecode));
    productTable.clear();
    productTable.setRowCount(0);
    productTable.setHorizontalHeaderLabels({"Модель","Номер","Дата", "Событие"});
    barecoceImg = barecode;
    productTable.insertRow(0);
    productTable.setCellWidget(0,0, new QLabel(data.productType));
    productTable.setCellWidget(0,1, new QLabel(data.id));
    productTable.setCellWidget(0,2, new QLabel("Добавлено"));
    productTable.setCellWidget(0,3, new QLabel(data.dateOfAdd));

    productTable.insertRow(1);
    productTable.setCellWidget(1,0, new QLabel(data.productType));
    productTable.setCellWidget(1,1, new QLabel(data.id));
    productTable.setCellWidget(1,2, new QLabel("Собрано"));
    productTable.setCellWidget(1,3, new QLabel(data.dateOfBuild));

    productTable.insertRow(2);
    productTable.setCellWidget(2,0, new QLabel(data.productType));
    productTable.setCellWidget(2,1, new QLabel(data.id));
    productTable.setCellWidget(2,2, new QLabel("Прошло регулировку"));
    productTable.setCellWidget(2,3, new QLabel(data.dateOfAdjustment));

    productTable.insertRow(3);
    productTable.setCellWidget(3,0, new QLabel(data.productType));
    productTable.setCellWidget(3,1, new QLabel(data.id));
    productTable.setCellWidget(3,2, new QLabel("Прошло ОТК"));
    productTable.setCellWidget(3,3, new QLabel(data.dateOfOtk));

    productTable.insertRow(4);
    productTable.setCellWidget(4,0, new QLabel(data.productType));
    productTable.setCellWidget(4,1, new QLabel(data.id));
    productTable.setCellWidget(4,2, new QLabel("Отгружено"));
    productTable.setCellWidget(4,3, new QLabel(data.dateOfShipping));

    productTable.resizeColumnsToContents();
    productTable.resizeRowsToContents();
}

void ProductTab::updateProductTypes(const QStringList types){
    productTypes.clear();
    productTypes.addItems(types);
}

void ProductTab::updateIds(const QStringList idList){
    this->productIds.clear();
    productIds.addItems(idList);
}

QComboBox *ProductTab::getProductTypesComboBox(){return &productTypes;}

QComboBox *ProductTab::getProductIdsComboBox(){return &productIds;}

const QPushButton *ProductTab::getPrintBareCodePushButton(){return  &printBareCodeBtn;}

const QPushButton *ProductTab::getSaveBareCodeInFilePushButton(){return &saveBareCodeInFileBtn;}

const QString ProductTab::cetCurrentProductType(){return productTypes.currentText();}

void ProductTab::onClickedPrintBareCode()
{
    qDebug()<<"onClickedPrintBareCode\n";
    emit needPrintBarecode({barecoceImg});
}

void ProductTab::onClickedSaveBareCodeInFile()
{
    qDebug()<<"onClickedSaveBareCodeInFile\n";
    QString filename = QInputDialog::getText(this, "Введите имя файла", "имя файла");
    emit needSaveBarecode({barecoceImg}, filename);
}
