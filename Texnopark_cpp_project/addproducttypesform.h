#ifndef ADDPRODUCTTYPESFORM_H
#define ADDPRODUCTTYPESFORM_H

#include <QtWidgets>
#include <structuresForTable.h>

class AddProductTypesForm : public QDialog
{
    Q_OBJECT
public:
    explicit AddProductTypesForm(QWidget *parent = nullptr);
    const QPushButton* getSubmitButton();
    const QString getCurrentProductTypeNameInput();
    void setProductTypeName(const QString& name);
    ~AddProductTypesForm(){}
private:
    QLineEdit productTypeNameInput;
    QPushButton submit;
};

#endif // ADDPRODUCTTYPESFORM_H
