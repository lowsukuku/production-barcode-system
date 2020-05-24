#ifndef AUTHORIZATIONFORM_H
#define AUTHORIZATIONFORM_H
#include <QtWidgets>
#include <QCloseEvent>
#include <structuresForTable.h>

class AuthorizationForm : public QDialog
{

public:
    explicit AuthorizationForm(QWidget *parent = nullptr);
    const QString getUserName();
    const QString getPassword();
    void setUserName(const QString& name);
    void setPassword(const QString& pswd);
    const QPushButton* getButtonEnter();
    void  afterLoginRequest(bool isAuthorized);
protected: void closeEvent(QCloseEvent *event);
private:
    QLineEdit userName;
    QLineEdit password;
    QPushButton enter;
};

#endif // AUTHORIZATIONFORM_H
