#ifndef TST_MYTEST_H
#define TST_MYTEST_H

#include <QObject>
#include <QtWidgets>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "addproductform.h"
#include <QApplication>
#include "producttab.h"
using namespace testing;

TEST(Tests, MyTest)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}



class Receiver : public QObject
{

    Q_OBJECT
    public slots:
    virtual void someSlot(const QList<QImage>& img) = 0;

};


class MockReceiver : public Receiver
{
    Q_OBJECT
public:
    MOCK_METHOD1( someSlot, void(const QList<QImage>& img) );
};


TEST( testSaveBarecodeSignal, emitSignalFromAddProductForm )
{
    int argc=0;
    char** argv = nullptr;
    QApplication a(argc,argv);
    MockReceiver receiver;
    AddProductForm sender;
    QObject::connect(&sender, &AddProductForm::needSaveBarecode, &receiver, &MockReceiver::someSlot);
    const QList<QImage> img;
    EXPECT_CALL( receiver, someSlot(img) ).Times(1);
    emit sender.needSaveBarecode({});
}

TEST( testSaveBarecodeSignal, noEmitsSignalFromAddProductForm )
{
    int argc=0;
    char** argv = nullptr;
    QApplication a(argc,argv);
    MockReceiver receiver;
    AddProductForm sender;
    QObject::connect(&sender, &AddProductForm::needSaveBarecode, &receiver, &MockReceiver::someSlot);
    const QList<QImage> img;
    EXPECT_CALL( receiver, someSlot(img) ).Times(0);
}





TEST( testSaveBarecodeSignal, emitSignalFromProductTab )
{
    int argc=0;
    char** argv = nullptr;
    QApplication a(argc,argv);
    MockReceiver receiver;
    ProductTab sender;
    QObject::connect(&sender, &ProductTab::needSaveBarecode, &receiver, &MockReceiver::someSlot);
    const QList<QImage> img;
    EXPECT_CALL( receiver, someSlot(img) ).Times(1);
    emit sender.needSaveBarecode({});
}

TEST( testSaveBarecodeSignal, noEmitsSignalFromProductTab )
{
    int argc=0;
    char** argv = nullptr;
    QApplication a(argc,argv);
    MockReceiver receiver;
    ProductTab sender;
    QObject::connect(&sender, &ProductTab::needSaveBarecode, &receiver, &MockReceiver::someSlot);
    const QList<QImage> img;
    EXPECT_CALL( receiver, someSlot(img) ).Times(0);
}


TEST( testPrintBarecodeSignal, emitSignalFromProductTab )
{
    int argc=0;
    char** argv = nullptr;
    QApplication a(argc,argv);
    MockReceiver receiver;
    ProductTab sender;
    QObject::connect(&sender, &ProductTab::needPrintBarecode, &receiver, &MockReceiver::someSlot);
    const QList<QImage> img;
    EXPECT_CALL( receiver, someSlot(img) ).Times(1);
    emit sender.needPrintBarecode({});

}

TEST( testPrintBarecodeSignal, noEmitSignalFromProductTab )
{
    int argc=0;
    char** argv = nullptr;
    QApplication a(argc,argv);
    MockReceiver receiver;
    ProductTab sender;
    QObject::connect(&sender, &ProductTab::needPrintBarecode, &receiver, &MockReceiver::someSlot);
    const QList<QImage> img;
    EXPECT_CALL( receiver, someSlot(img) ).Times(0);
}

TEST( testPrintBarecodeSignal, emitSignalFromAddProductForm )
{
    int argc=0;
    char** argv = nullptr;
    QApplication a(argc,argv);
    MockReceiver receiver;
    AddProductForm sender;
    QObject::connect(&sender, &AddProductForm::needPrintBarecode, &receiver, &MockReceiver::someSlot);
    const QList<QImage> img;
    EXPECT_CALL( receiver, someSlot(img) ).Times(1);
    emit sender.needPrintBarecode({});

}

TEST(testPrintBarecodeSignal, noEmitsSignalFromAddProductForm )
{
    int argc=0;
    char** argv = nullptr;
    QApplication a(argc,argv);
    MockReceiver receiver;
    AddProductForm sender;
    QObject::connect(&sender, &AddProductForm::needSaveBarecode, &receiver, &MockReceiver::someSlot);
    const QList<QImage> img;
    EXPECT_CALL( receiver, someSlot(img) ).Times(0);
}






#endif // TST_MYTEST_H

