#include "addproducttypesform.h"

AddProductTypesForm::AddProductTypesForm(QWidget *parent):QDialog(parent)
{
    setModal(true);
    setWindowFlags (windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(("Добавление модели"));
    submit.setText("Добавить модель");
    productTypeNameInput.setPlaceholderText("Имя модели");
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(&productTypeNameInput);
    layout->addWidget(&submit);
    setLayout(layout);
    setMinimumWidth(220);
}

const QPushButton *AddProductTypesForm::getSubmitButton(){return &submit;}

const QString AddProductTypesForm::getCurrentProductTypeNameInput(){return productTypeNameInput.text();}

void AddProductTypesForm::setProductTypeName(const QString &name){productTypeNameInput.setText(name);}
