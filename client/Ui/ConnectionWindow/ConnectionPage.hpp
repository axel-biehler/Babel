//
// Created by max on 27/09/2021.
//

#ifndef BABEL_CONNECTIONPAGE_HPP
#define BABEL_CONNECTIONPAGE_HPP

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>

namespace Babel {
    namespace Ui {
        class ConnectionPage : public QWidget {
        public:
            ConnectionPage(QWidget *parent = 0);
            ~ConnectionPage() = default;
        private:
            QLineEdit _input;
            QVBoxLayout _mainLayout;
            QHBoxLayout _btnLayout;
            QWidget _btnWidget;
            QLabel _text;
            QPushButton *_register;
            QPushButton *_login;
        };
    }
}

#endif //BABEL_CONNECTIONPAGE_HPP
