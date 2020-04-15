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
    void test_case1();
    void testTabBar();
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

void gui_test::test_case1()
{
    QLineEdit a;
    QTest::keyClicks(&a, "abCDEf123-");

    QCOMPARE(a.text(), QString("abCDEf123-"));
    QVERIFY(a.isModified());
}


void gui_test::testTabBar()
{
    MainWindow w;
    w.authorizationForm->afterLoginRequest(true);

    QCOMPARE(w.tabWidget->currentIndex(), 0);
//    QTest::mouseClick(w.tabWidget->tabBar()->tabButton(1,QTabBar::RightSide),Qt::MouseButton::LeftButton);
}

QTEST_MAIN(gui_test)

#include "tst_gui_test.moc"
