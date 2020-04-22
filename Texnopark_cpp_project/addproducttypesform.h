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
    void setProductTypeName(const QString& name){productTypeNameInput.setText(name);}
    ~AddProductTypesForm(){}
private:
    QLineEdit productTypeNameInput;
    QPushButton submit;
};

#endif // ADDPRODUCTTYPESFORM_H
