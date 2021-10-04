//
// Created by max on 27/09/2021.
//

#include <QWidget>
#include "Window.hpp"
#include <QLineEdit>
#include "ConnexionPage.hpp"

Babel::Ui::Window::Window(QWidget *parent) {
    this->setFixedSize(600, 400);
    setWindowTitle("Connection");
    Babel::Ui::ConnexionPage *page = new Babel::Ui::ConnexionPage;

    _pages.addWidget(page);
    _layout.addWidget(&_pages);

    this->setLayout(&_layout);
    show();
}

Babel::Ui::Window::~Window() noexcept {

}