#ifndef CONTROLLERFORBARECODE_H
#define CONTROLLERFORBARECODE_H

#include <QObject>

class ControllerForBarecode : public QObject
{
    Q_OBJECT

public:
    explicit ControllerForBarecode(QObject *parent = nullptr);
    ~ControllerForBarecode(){}
    bool printBarecode(const QImage& img);
    bool saveBarecodeInFile(const QImage& img);
    QImage transformIdToBarecode(const QString& id);

};



#endif // CONTROLLERFORBARECODE_H
