#ifndef AUTHORIZATIONFORM_H
#define AUTHORIZATIONFORM_H
#include <QtWidgets>
#include <QCloseEvent>
class AuthorizationForm : public QDialog
{

public:
    explicit AuthorizationForm(QWidget *parent = nullptr);
    const QString getUserName(){return  userName.text();}
    const QString getPassword(){return password.text();}
    const QPushButton* getButtonEnter(){return &enter;}
    void  afterLoginRequest(bool isAuthorized);
protected: void closeEvent(QCloseEvent *event)
    {
        qDebug()<<"Крестик\n";
        exit(0);
        event->accept();
    }
private:
    QLineEdit userName;
    QLineEdit password;
    QPushButton enter;
};

#endif // AUTHORIZATIONFORM_H
