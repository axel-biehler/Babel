//
// Created by max on 27/09/2021.
//

#include "ConnexionPage.hpp"

Babel::Ui::ConnexionPage::ConnexionPage(QWidget *parent) {
    _input.setPlaceholderText("Username");
    _layout.addWidget(&_input, Qt::AlignCenter);
    //_layout.setGeometry({100, 100, 100, 100});
    _register = new QPushButton("Register", this);
    _login = new QPushButton("Log In", this);
    _layout.addWidget(_register);
    _layout.addWidget(_login);
    this->setLayout(&_layout);
}