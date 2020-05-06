#include "controllerforbarecode.h"

ControllerForBarecode::ControllerForBarecode(QObject *parent) : QObject(parent)
{

}


bool ControllerForBarecode::printBarecode(const QImage &img)
{
    qDebug()<<"ControllerForBarecode::printBarecode"<<"\n";
    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer,0);
    if(dlg->exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.drawImage(QPoint(0,0),img);
        painter.end();
    }
    delete dlg;
    return true;
}

bool ControllerForBarecode::saveBarecodeInFile(const QImage &img, const QString fileName)
{
    qDebug()<<"ControllerForBarecode::saveBarecodeInFile "<<fileName<<"\n";
    img.save(fileName,"png");
    return true;
}

QImage ControllerForBarecode::transformIdToBarecode(const QString &id)
{
    QScopedPointer<Prison::AbstractBarcode> barcode;
    barcode.reset(Prison::createBarcode(Prison::DataMatrix));
    barcode->setData(id);
    QImage result = barcode->toImage(QSizeF(25,25));
    result.save("id","png");
    return result;

}
