#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "authorizationform.h"
#include "allproductstab.h"
#include "productsbytypestab.h"
#include "producttab.h"
#include "producttypestab.h"
#include "addproducttypesform.h"
#include "addproductform.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    AuthorizationForm* authorizationForm;
    QTabWidget *tabWidget;
    QPushButton* addProtuctTypeBtn;
    QPushButton* addProtuctBtn;
    AddProductTypesForm* addProductTypesForm;
    AddProductForm* addProductForm;

    ProductTypesTab* prodTypesTab;
    AllProductsTab* allProductsTab;
    ProductsByTypesTab* prodByTypesTab;
    ProductTab* prodTab;

public slots:
    void onClickedAddProtuctTypeBtn();
    void onClickedAddProtuctBtn();
    void onClickedTabBar(int index);
    //для формы добавления продукта
    void formAddProdOnClickedSubmit();

    //для формы добавления модели
    void formAddProdTypeClickedSubmit();

    //для таба изделия по моделям
    void tabProdByTypesChangedTypes(const QString &text);

    //для таба отдельного изделия
    void tabProdChangeTypes(const QString &text);
    void tabProdChangeId(const QString &text);

    //для штрих-кодов
    void printBarecode(const QList<QImage>& img);
    void saveBarecode(const QList<QImage>& img);

    //для авторизации
     void authorizate();


};
#endif // MAINWINDOW_H
