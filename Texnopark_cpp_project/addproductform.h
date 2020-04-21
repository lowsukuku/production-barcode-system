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
    void setCurrentProductType(const QString& type){}
    const QPushButton* getSubmitButton(){return &submit;}
    const QPushButton* getSaveBarecodeButton(){return &saveBareCodeInFileBtn;}
     const QPushButton* getPrintBarecodeButton(){return &printBareCodeBtn;}
    void updateAfterSubmit(const QStringList& ids, const QList<QImage>& barecodes);
    void setBarecodeButtonsHidden(){
        printBareCodeBtn.setHidden(true);
        saveBareCodeInFileBtn.setHidden(true);
    }
    bool isBarecodeButtonsHidden(){return printBareCodeBtn.isHidden()&&saveBareCodeInFileBtn.isHidden();}
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
