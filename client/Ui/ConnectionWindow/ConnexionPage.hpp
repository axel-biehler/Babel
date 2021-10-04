//
// Created by max on 27/09/2021.
//

#ifndef BABEL_CONNEXIONPAGE_HPP
#define BABEL_CONNEXIONPAGE_HPP

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>

namespace Babel {
    namespace Ui {
        class ConnexionPage : public QWidget {
        public:
            ConnexionPage(QWidget *parent = 0);
            ~ConnexionPage() = default;
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

#endif //BABEL_CONNEXIONPAGE_HPP
