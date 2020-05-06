#ifndef ADDPRODUCTFORM_H
#define ADDPRODUCTFORM_H

#include "controllerforbarecode.h"
#include <QtWidgets>
#include <structuresForTable.h>

class AddProductForm : public QDialog
{
    Q_OBJECT
public:
    explicit AddProductForm(QWidget *parent = nullptr );

    const QString getCurrentProductType();
    const QString getCurrentAmount();
    void setCurrentProductType(const QString& type){}
    QPushButton* getSubmitButton(){return &submit;}
    const QPushButton* getSaveBarecodeButton(){return &saveBareCodeInFileBtn;}
    const QPushButton* getPrintBarecodeButton(){return &printBareCodeBtn;}
    void updateAfterSubmit(const QStringList& ids, const QList<QImage>& barecodes);
    void clearState();
    void updateProductTypes(const QStringList types);
    bool isBarecodeButtonsHidden(){return printBareCodeBtn.isHidden()&&saveBareCodeInFileBtn.isHidden();}
    ~AddProductForm();
signals:
    void needPrintBarecode(const QList<QImage>& img);
    void needSaveBarecode(const QList<QImage>& img, const QString& filename);
private:
    QPushButton submit;
    QComboBox productTypes;
    QSpinBox amountOfProducts;
    QPushButton printBareCodeBtn;
    QPushButton saveBareCodeInFileBtn;
    QVBoxLayout layout;
    QGridLayout imgLayout;
    QList<QImage> imgList;

protected: void closeEvent(QCloseEvent *event)
    {
        clearState();
    }
private slots:
    void onClickedPrintBareCode();
    void onClickedSaveBareCodeInFile();
};


#endif // ADDPRODUCTFORM_H
