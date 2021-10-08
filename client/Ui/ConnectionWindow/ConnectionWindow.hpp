//
// Created by max on 27/09/2021.
//

#ifndef BABEL_CONNECTIONWINDOW_HPP
#define BABEL_CONNECTIONWINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>

namespace Babel {
    namespace Ui {
        class ConnectionWindow : public QWidget {
        public:
            ConnectionWindow(QWidget *parent = 0);
            ~ConnectionWindow();
        private:
            QStackedWidget _pages;
            QGridLayout *_layout;
        };
    }
}

#endif //BABEL_CONNECTIONWINDOW_HPP
