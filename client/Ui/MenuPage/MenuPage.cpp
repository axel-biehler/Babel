//
// Created by max on 27/09/2021.
//

#include "./MenuPage.hpp"
#include <QLineEdit>

MenuPage::MenuPage(QWidget *parent) {
    QLineEdit *input = new QLineEdit("", this);
    input->setGeometry(100, 100, 100, 100);
    input->setPlaceholderText("test");
}