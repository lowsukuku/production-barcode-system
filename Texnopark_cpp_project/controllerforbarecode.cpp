#include "controllerforbarecode.h"
#include <QImage>

ControllerForBarecode::ControllerForBarecode(QObject *parent) : QObject(parent)
{

}


bool ControllerForBarecode::printBarecode(const QImage &img)
{
    return true;
}

bool ControllerForBarecode::saveBarecodeInFile(const QImage &img)
{
    return true;
}

QImage ControllerForBarecode::transformIdToBarecode(const QString &id)
{
    QImage img;
    return img;

}
