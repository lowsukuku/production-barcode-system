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
    layout.addLayout(&imgLayout);
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

QPushButton *AddProductForm::getSubmitButton(){return &submit;}

const QPushButton *AddProductForm::getSaveBarecodeButton(){return &saveBareCodeInFileBtn;}

const QPushButton *AddProductForm::getPrintBarecodeButton(){return &printBareCodeBtn;}

void AddProductForm::updateAfterSubmit(const QStringList &ids, const QList<QImage> &barecodes)
{
    //заполняем layout кнопками и т.д.
    if(ids.empty()){
        (new QErrorMessage(this))->showMessage("Возникла ошибка, проверьте соединение с интернетом и попробуйте снова");
        clearState();
        hide();
        return;
    }

    auto idIter = ids.begin();
    auto imgIter = barecodes.begin();
    for(int i = 0; i< ids.length(); ++i){
        imgLayout.addWidget(new QLabel(*idIter));
        QLabel* imgLabel = new QLabel();
        imgLabel->resize(imgIter->size());
        imgLabel->setPixmap(QPixmap::fromImage(*imgIter));
        imgLayout.addWidget(imgLabel);
        imgIter->save(*idIter + ".png","png");

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
    emit needPrintBarecode(imgList);
    clearState();
    hide();

}

void AddProductForm::onClickedSaveBareCodeInFile()
{
     qDebug()<<"onClickedSaveBareCodeInFile\n";
     QString filename = QInputDialog::getText(this, "Введите имя файла", "имя файла");
     emit needSaveBarecode(imgList, filename);
     clearState();
     hide();

}
