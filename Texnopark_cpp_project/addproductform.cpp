#include "addproductform.h"

AddProductForm::AddProductForm(QWidget *parent):QDialog(parent)
{

    setModal(true);
    setWindowFlags (windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(("Добавление изделия"));
    submit.setText("Добавить изделия");

    saveBareCodeInFileBtn.setText("Сохранить в файл");
    printBareCodeBtn.setText("Печать");
    saveBareCodeInFileBtn.setHidden(true);
    printBareCodeBtn.setHidden(true);
    amountOfProducts.setMinimum(1);
    layout.addWidget(&productTypes);
    layout.addWidget(&amountOfProducts);
    layout.addWidget(&submit);
    layout.addWidget(&printBareCodeBtn);
    layout.addWidget(&saveBareCodeInFileBtn);

    setLayout(&layout);
    setMinimumWidth(220);
    connect(&printBareCodeBtn, SIGNAL(clicked()), this, SLOT(onClickedPrintBareCode()));
    connect(&saveBareCodeInFileBtn, SIGNAL(clicked()), this, SLOT(onClickedSaveBareCodeInFile()));
}

AddProductForm::~AddProductForm()
{
qDebug()<<"AddProductForm";
}

const QString AddProductForm::getCurrentProductType()
{
    return productTypes.currentText();
}

const QString AddProductForm::getCurrentAmount()
{
    return QString::number(amountOfProducts.value());
}

void AddProductForm::updateAfterSubmit(const QStringList &ids, const QList<QImage> &barecodes)
{
    //заполняем layout кнопками и т.д.
    auto idIter = ids.begin();
    auto imgIter = barecodes.begin();
    for(int i = 0; i< ids.length(); ++i){
        imgLayout.addWidget(new QLabel(*idIter));
        QLabel* imgLabel = new QLabel();
        imgLabel->resize(imgIter->size());
        imgLabel->setPixmap(QPixmap::fromImage(*imgIter));
        imgLayout.addWidget(imgLabel);
        imgIter->save(*idIter + ".png","png");
        layout.addLayout(&imgLayout);
        imgIter++;
        idIter++;

    }
    imgList = barecodes;
    submit.setHidden(true);
    printBareCodeBtn.setHidden(false);
    saveBareCodeInFileBtn.setHidden(false);
}

void AddProductForm::clearState(){
    imgList.clear();
    while (QLayoutItem* item = imgLayout.takeAt(0)) {
        delete item->widget();
        delete item;
    }
    printBareCodeBtn.setHidden(true);
    saveBareCodeInFileBtn.setHidden(true);
}

void AddProductForm::updateProductTypes(const QStringList types)
{
    productTypes.clear();
    productTypes.addItems(types);
}

void AddProductForm::onClickedPrintBareCode()
{
    qDebug()<<"onClickedPrintBareCode\n";
    clearState();
    hide();
    emit needPrintBarecode(imgList);
}

void AddProductForm::onClickedSaveBareCodeInFile()
{
     qDebug()<<"onClickedSaveBareCodeInFile\n";
     clearState();
     hide();
     QString filename = QInputDialog::getText(this, "Введите имя файла", "имя файла");
     emit needSaveBarecode(imgList, filename);
}
