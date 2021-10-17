//
// Created by max on 27/09/2021.
//

#include <QWidget>
#include <Networking/Client.hpp>
#include "ConnectionWindow.hpp"
#include "ConnectionPage.hpp"

Babel::Ui::ConnectionWindow::ConnectionWindow(Babel::Networking::Client *cli): _connectionPage(cli, this) {
    setFixedSize(600, 400);
    setWindowTitle("Connection");

    setLayout(&_layout);
   _connectionPage.setParent(this);
    _layout.addWidget(&_connectionPage);

    show();
}