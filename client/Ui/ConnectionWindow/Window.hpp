//
// Created by max on 27/09/2021.
//

#ifndef BABEL_WINDOW_HPP
#define BABEL_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>

namespace Babel {
    namespace Ui {
        class Window : public QWidget {
        public:
            Window(QWidget *parent = 0);
            ~Window();
        private:
            QStackedWidget _pages;
            QGridLayout *_layout;
        };
    }
}

#endif //BABEL_WINDOW_HPP
