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

void AuthorizationForm::afterLoginRequest(bool isAuthorized)
{
    if(isAuthorized)
        this->hide();
    else{
        (new QErrorMessage(this))->showMessage("Неправильный логин или пароль, попробуйте снова");
    }
}
