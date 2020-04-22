#include "addproductform.h"

AddProductForm::AddProductForm(QWidget *parent):QDialog(parent)
{

    setModal(true);
    setWindowFlags (windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(("Добавление изделия"));
    submit.setText("Добавить изделия");
    productTypes.addItems({"type1", "type2", "type3"});
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
    printBareCodeBtn.setHidden(false);
    saveBareCodeInFileBtn.setHidden(false);

}

void AddProductForm::onClickedPrintBareCode()
{
    qDebug()<<"onClickedPrintBareCode\n";
    setBarecodeButtonsHidden();
    hide();
    emit needPrintBarecode({});
}

void AddProductForm::onClickedSaveBareCodeInFile()
{
     qDebug()<<"onClickedSaveBareCodeInFile\n";
     setBarecodeButtonsHidden();
     hide();
     emit needSaveBarecode({});
}
