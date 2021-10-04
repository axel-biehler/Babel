//
// Created by max on 27/09/2021.
//

#include "ConnexionPage.hpp"

Babel::Ui::ConnexionPage::ConnexionPage(QWidget *parent) {
    _text.setText("Enter Username:");
    _text.setAlignment(Qt::AlignCenter);
    _mainLayout.addWidget(&_text);
    _input.setPlaceholderText("Username");
    _mainLayout.addWidget(&_input, Qt::AlignCenter);
    //_layout.setGeometry({100, 100, 100, 100});
    _register = new QPushButton("Sign Up", this);
    _login = new QPushButton("Sign In", this);
    _mainLayout.addWidget(&_btnWidget);
    _btnWidget.setLayout(&_btnLayout);
    _btnLayout.addWidget(_login);
    _btnLayout.addWidget(_register);
    this->setLayout(&_mainLayout);
}