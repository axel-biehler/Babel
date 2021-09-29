//
// Created by max on 27/09/2021.
//

#include "./ConnexionPage.hpp"
#include <QLineEdit>
#include <QFormLayout>

ConnexionPage::ConnexionPage(QWidget *parent) {
    QFormLayout *formLayout = new QFormLayout;
    QLineEdit *input = new QLineEdit("", this);
    //input->setGeometry(100, 100, 100, 100);
    input->setPlaceholderText("Username");
    formLayout->addRow("UserName:", input);
    formLayout->setGeometry({100, 100, 100, 100});
}