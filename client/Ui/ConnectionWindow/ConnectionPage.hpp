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
        Q_OBJECT
        public:
            ConnectionPage(QWidget *parent = 0);
            ~ConnectionPage() = default;
        private:
            QLineEdit _input;
            QLineEdit _pass;
            QLineEdit _ip;
            QVBoxLayout _mainLayout;
            QHBoxLayout _btnLayout;
            QWidget _btnWidget;
            QLabel _text;
            QPushButton *_register;
            QPushButton *_login;

        private slots:
            void Register();
            void Login();
        };
    }
}

#endif //BABEL_CONNECTIONPAGE_HPP
