#ifndef ADDPRODUCTTYPESFORM_H
#define ADDPRODUCTTYPESFORM_H

#include <QtWidgets>

class AddProductTypesForm : public QDialog
{
    Q_OBJECT
public:
    explicit AddProductTypesForm(QWidget *parent = nullptr);
    const QPushButton* getSubmitButton(){return &submit;}
    const QString getCurrentProductTypeNameInput(){return productTypeNameInput.text();}
    ~AddProductTypesForm(){}
private:
    QLineEdit productTypeNameInput;
    QPushButton submit;
};

#endif // ADDPRODUCTTYPESFORM_H
