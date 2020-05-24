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
    QComboBox* getProductTypesComboBox();
    QComboBox* getProductIdsComboBox();
    const QPushButton* getPrintBareCodePushButton();
    const QPushButton* getSaveBareCodeInFilePushButton();
    const QString cetCurrentProductType();
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
    QLabel barecodeImgLabel;
    QImage barecoceImg;
private slots:
    void onClickedPrintBareCode();
    void onClickedSaveBareCodeInFile();

};

#endif // PRODUCTTAB_H
