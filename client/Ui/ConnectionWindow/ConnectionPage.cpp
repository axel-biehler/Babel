//
// Created by max on 27/09/2021.
//

#include "ConnectionPage.hpp"

Babel::Ui::ConnectionPage::ConnectionPage(QWidget *parent) {
    _text.setText("Enter connection informations :");
    _text.setAlignment(Qt::AlignCenter);
    _mainLayout.addWidget(&_text);
    _input.setPlaceholderText("Username");
    _pass.setPlaceholderText("Password");
    _ip.setPlaceholderText("IP");
    _mainLayout.addWidget(&_input, Qt::AlignCenter);
    _mainLayout.addWidget(&_pass, Qt::AlignCenter);
    _mainLayout.addWidget(&_ip, Qt::AlignCenter);
    //_layout.setGeometry({100, 100, 100, 100});
    _register = new QPushButton("Sign Up", this);
    QObject::connect(_register, &QPushButton::released, this, &Babel::Ui::ConnectionPage::Register);
    QObject::connect(_login, &QPushButton::released, this, &Babel::Ui::ConnectionPage::Login);
    _login = new QPushButton("Sign In", this);
    _mainLayout.addWidget(&_btnWidget);
    _btnWidget.setLayout(&_btnLayout);
    _btnLayout.addWidget(_login);
    _btnLayout.addWidget(_register);
    this->setLayout(&_mainLayout);
}

void Babel::Ui::ConnectionPage::Register()
{
}

void Babel::Ui::ConnectionPage::Login()
{

}