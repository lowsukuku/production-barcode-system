#ifndef ADDPRODUCTFORM_H
#define ADDPRODUCTFORM_H

#include "controllerforbarecode.h"
#include <QtWidgets>

class AddProductForm : public QDialog
{
    Q_OBJECT
public:
    explicit AddProductForm(QWidget *parent = nullptr );

    const QString getCurrentProductType();
    const QString getCurrentAmount();
    const QPushButton* getSubmitButton(){return &submit;}
    void updateAfterSubmit(const QStringList& ids, const QList<QImage>& barecodes);
    void setBarecodeButtonsHidden(){
        printBareCodeBtn.setHidden(true);
        saveBareCodeInFileBtn.setHidden(true);
    }
     ~AddProductForm();
signals:
   void needPrintBarecode(const QList<QImage>& img);
   void needSaveBarecode(const QList<QImage>& img);
private:
    QPushButton submit;
    QComboBox productTypes;
    QSpinBox amountOfProducts;
    QPushButton printBareCodeBtn;
    QPushButton saveBareCodeInFileBtn;
    QVBoxLayout layout;
private slots:
    void onClickedPrintBareCode();
    void onClickedSaveBareCodeInFile();
};

#endif // ADDPRODUCTFORM_H
