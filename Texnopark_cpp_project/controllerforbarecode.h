#ifndef CONTROLLERFORBARECODE_H
#define CONTROLLERFORBARECODE_H

#include <QObject>
#include <QImage>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include <QDebug>
#include <QDateTime>
#include <structuresForTable.h>
#include "prison.h"
#include "abstractbarcode.h"
#include <qstringlist.h>
#include <QImageWriter>



class ControllerForBarecode : public QObject
{
    Q_OBJECT

public:
    explicit ControllerForBarecode(QObject *parent = nullptr);
    ~ControllerForBarecode(){}
    bool printBarecode(const QImage& img);
    bool saveBarecodeInFile(const QImage& img, const QString fineName);
    QImage transformIdToBarecode(const QString& id);

};



#endif // CONTROLLERFORBARECODE_H
