//
// Created by max on 27/09/2021.
//

#include "ConnexionPage.hpp"

ConnexionPage::ConnexionPage(QWidget *parent) {
    _input.setPlaceholderText("Username");
    _layout.addRow("UserName:", &_input);
    _layout.setGeometry({100, 100, 100, 100});
    setLayout(&_layout);
}