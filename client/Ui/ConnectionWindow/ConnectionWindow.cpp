//
// Created by max on 27/09/2021.
//

#include <QWidget>
#include "ConnectionWindow.hpp"
#include <QLineEdit>
#include "ConnectionPage.hpp"

Babel::Ui::ConnectionWindow::ConnectionWindow(QWidget *parent) {
    this->setMinimumSize(600, 400);
    setWindowTitle("Connection");
    Babel::Ui::ConnectionPage *page = new Babel::Ui::ConnectionPage;
    _layout = new QGridLayout(this);
    _pages.addWidget(page);
    _pages.setFixedSize(width() / 2, height() / 2);
    _layout->addWidget(&_pages, 0, 0,Qt::AlignCenter);

    this->setLayout(_layout);
    show();
}

Babel::Ui::ConnectionWindow::~ConnectionWindow() noexcept {

}