#include "authorizationform.h"

AuthorizationForm::AuthorizationForm(QWidget *parent):QDialog(parent)
{
    setModal(true);
    setWindowFlags (windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(("Авторизация пользователя"));
    userName.setPlaceholderText("имя пользователя");
    password.setPlaceholderText("Пароль");
    password.setEchoMode(QLineEdit::Password);
    enter.setText("Войти");
    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addWidget(&userName);
    vLayout->addWidget(&password);
    vLayout->addWidget(&enter);
    setLayout(vLayout);
    this->setMinimumWidth(300);
}

const QString AuthorizationForm::getUserName(){return  userName.text();}

const QString AuthorizationForm::getPassword(){return password.text();}

void AuthorizationForm::setUserName(const QString &name){userName.setText(name);}

void AuthorizationForm::setPassword(const QString &pswd){password.setText(pswd);}

const QPushButton *AuthorizationForm::getButtonEnter(){return &enter;}

void AuthorizationForm::afterLoginRequest(bool isAuthorized)
{
    if(isAuthorized)
        this->hide();
    else{
        (new QErrorMessage(this))->showMessage("Неправильный логин или пароль, попробуйте снова");
    }
}

void AuthorizationForm::closeEvent(QCloseEvent *event)
{
    qDebug()<<"Крестик\n";
    exit(0);
    event->accept();
}
