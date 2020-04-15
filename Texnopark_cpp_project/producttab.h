#ifndef PRODUCTTAB_H
#define PRODUCTTAB_H

#include <QtWidgets>
#include "controllerforbarecode.h"

class ProductTab : public QWidget
{
    Q_OBJECT
public:
    explicit ProductTab(QWidget *parent = nullptr);
    void updateTableData(const QStringList data);
    void updateProductTypes(const QStringList productTypes);
    void updateIds(const QStringList idList);
    const QComboBox* getProductTypesComboBox(){return &productTypes;}
    const QComboBox* getProductIdsComboBox(){return &productIds;}
    const QPushButton* getPrintBareCodePushButton(){return  &printBareCodeBtn;}
    const QPushButton* getSaveBareCodeInFilePushButton(){return &saveBareCodeInFileBtn;}
    const QString cetCurrentProductType(){return productTypes.currentText();}
    ~ProductTab(){}
signals:
    void  needPrintBarecode(const QList<QImage>& img);
    void needSaveBarecode(const QList<QImage>& img);
private:
    QVBoxLayout layout;
    QTableWidget productTable;
    QComboBox productTypes;
    QComboBox productIds;
    QPushButton printBareCodeBtn;
    QPushButton saveBareCodeInFileBtn;
private slots:
    void onClickedPrintBareCode();
    void onClickedSaveBareCodeInFile();

};

#endif // PRODUCTTAB_H
