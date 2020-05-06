#ifndef PRODUCTTAB_H
#define PRODUCTTAB_H

#include <QtWidgets>
#include "controllerforbarecode.h"
#include <structuresForTable.h>

class ProductTab : public QWidget
{
    Q_OBJECT
public:
    explicit ProductTab(QWidget *parent = nullptr);
    void updateTableDateAndBarecode(const ProductHistory& data, const QImage& barecode);
    void updateProductTypes(const QStringList productTypes);
    void updateIds(const QStringList idList);
    QComboBox* getProductTypesComboBox(){return &productTypes;}
    QComboBox* getProductIdsComboBox(){return &productIds;}
    const QPushButton* getPrintBareCodePushButton(){return  &printBareCodeBtn;}
    const QPushButton* getSaveBareCodeInFilePushButton(){return &saveBareCodeInFileBtn;}
    const QString cetCurrentProductType(){return productTypes.currentText();}
    ~ProductTab(){}
signals:
    void  needPrintBarecode(const QList<QImage>& img);
    void needSaveBarecode(const QList<QImage>& img, const QString& filename);
private:
    QVBoxLayout layout;
    QTableWidget productTable;
    QComboBox productTypes;
    QComboBox productIds;
    QPushButton printBareCodeBtn;
    QPushButton saveBareCodeInFileBtn;
    QLabel barecodeImg;
private slots:
    void onClickedPrintBareCode();
    void onClickedSaveBareCodeInFile();

};

#endif // PRODUCTTAB_H
