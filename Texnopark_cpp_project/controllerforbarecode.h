#ifndef CONTROLLERFORBARECODE_H
#define CONTROLLERFORBARECODE_H

#include <QObject>
#include <QImage>

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
