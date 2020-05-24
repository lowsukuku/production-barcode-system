#include <QtTest>
#include <QCoreApplication>
#include <QtGui>
#include <QtWidgets>
#include <mainwindow.h>
// add necessary includes here

class gui_test : public QObject
{
    Q_OBJECT

public:
    gui_test();
    ~gui_test();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testChangeTabsByTablesClicked();
    void testAuthorizationFormTrue();
    void testAuthorizationFormFalse();
    void testAddproductTypesForm();
    void testAddPoductFormTrue1();
    void testAddPoductFormTrue2();

};

gui_test::gui_test()
{

}

gui_test::~gui_test()
{

}

void gui_test::initTestCase()
{

}

void gui_test::cleanupTestCase()
{

}



//тестируем переходы по вкладкам через таблицы
void gui_test::testChangeTabsByTablesClicked()
{

    MainWindow w;
    w.showMaximized();
    while ( !w.isVisible() ) {
         QTest::qWait(200);
    }
    w.authorizationForm->afterLoginRequest(true);
    QTest::qWait(1000);
    QWidget* wgt = w.prodTypesTab->getProductTypeTable()->cellWidget(0,0);
    QTest::mouseMove(wgt);
    QTest::mouseClick(wgt, Qt::MouseButton::LeftButton);
    QTest::mouseDClick(wgt, Qt::MouseButton::LeftButton);
    QCOMPARE(w.tabWidget->currentIndex(),2);
    QTest::qWait(100);
    QString txt1 = ((QLabel*)wgt)->text();
    QVERIFY(w.prodByTypesTab->getProductTypesComboBox()->currentText() == txt1);
    wgt = w.prodByTypesTab->getProductsTable()->cellWidget(0,0);
    QTest::mouseMove(wgt);
    QTest::mouseClick(wgt, Qt::MouseButton::LeftButton);
    QTest::mouseDClick(wgt, Qt::MouseButton::LeftButton);
    QCOMPARE(w.tabWidget->currentIndex(),3);
    QString txt2 = ((QLabel*)wgt)->text();
    QVERIFY(w.prodTab->getProductTypesComboBox()->currentText() == txt1);
    QVERIFY(w.prodTab->getProductIdsComboBox()->currentText() == txt2);
    w.close();
}

void gui_test::testAuthorizationFormTrue()
{
    MainWindow w;
    w.showMaximized();
    while ( !w.isVisible() ) {
         QTest::qWait(200);
    }
   QVERIFY(w.authorizationForm->isVisible());
   w.authorizationForm->setUserName("user");
   w.authorizationForm->setPassword("123456");
   QTest::mouseClick((QWidget*)w.authorizationForm->getButtonEnter(), Qt::MouseButton::LeftButton);
   QVERIFY(!w.authorizationForm->isVisible());
   w.close();
}

void gui_test::testAuthorizationFormFalse()
{
    MainWindow w;
    w.showMaximized();
    while ( !w.isVisible() ) {
         QTest::qWait(200);
    }
    QVERIFY(w.authorizationForm->isVisible());
    QTest::mouseClick((QWidget*)w.authorizationForm->getButtonEnter(), Qt::MouseButton::LeftButton);
    QVERIFY(w.authorizationForm->isVisible());
    w.close();
}

void gui_test::testAddproductTypesForm()
{
    MainWindow w;
    w.showMaximized();
    while ( !w.isVisible() ) {
         QTest::qWait(200);
    }
    w.authorizationForm->afterLoginRequest(true);
    QVERIFY(!w.addProductTypesForm->isVisible());
    QTest::mouseClick(w.addProtuctTypeBtn, Qt::MouseButton::LeftButton);
    QVERIFY(w.addProductTypesForm->isVisible());
    QTest::mouseClick((QWidget*)w.addProductTypesForm->getSubmitButton(), Qt::MouseButton::LeftButton);
    QVERIFY(!w.addProductTypesForm->isVisible());
    w.close();
}

void gui_test::testAddPoductFormTrue1()
{
    MainWindow w;
    w.showMaximized();
    while ( !w.isVisible() ) {
         QTest::qWait(200);
    }
    w.authorizationForm->afterLoginRequest(true);
    QVERIFY(!w.addProductForm->isVisible());
    //открыли форму
    QTest::mouseClick(w.addProtuctBtn, Qt::MouseButton::LeftButton);
    QVERIFY(w.addProductForm->isVisible());
    QVERIFY(w.addProductForm->isBarecodeButtonsHidden());
   //нажали добавить
    QTest::mouseClick((QWidget*)w.addProductForm->getSubmitButton(), Qt::MouseButton::LeftButton);
    QVERIFY(w.addProductForm->isVisible());
    QVERIFY(!w.addProductForm->isBarecodeButtonsHidden());
    //нажали на сохранить
    QTest::mouseClick((QWidget*)w.addProductForm->getSaveBarecodeButton(), Qt::MouseButton::LeftButton);
    QVERIFY(!w.addProductForm->isVisible());
    QVERIFY(w.addProductForm->isBarecodeButtonsHidden());

    w.close();
}

void gui_test::testAddPoductFormTrue2()
{
    MainWindow w;
    w.showMaximized();
    while ( !w.isVisible() ) {
         QTest::qWait(200);
    }
    w.authorizationForm->afterLoginRequest(true);
    QVERIFY(!w.addProductForm->isVisible());

    //открыли форму
    QTest::mouseClick(w.addProtuctBtn, Qt::MouseButton::LeftButton);
    QVERIFY(w.addProductForm->isVisible());
    QVERIFY(w.addProductForm->isBarecodeButtonsHidden());

    //нажали добавить
    QTest::mouseClick((QWidget*)w.addProductForm->getSubmitButton(), Qt::MouseButton::LeftButton);
    QVERIFY(w.addProductForm->isVisible());
    QVERIFY(!w.addProductForm->isBarecodeButtonsHidden());

    //нажали на печать
    QTest::mouseClick((QWidget*)w.addProductForm->getPrintBarecodeButton(), Qt::MouseButton::LeftButton);
    QVERIFY(!w.addProductForm->isVisible());
    QVERIFY(w.addProductForm->isBarecodeButtonsHidden());
    w.close();
}


QTEST_MAIN(gui_test)

#include "tst_gui_test.moc"
