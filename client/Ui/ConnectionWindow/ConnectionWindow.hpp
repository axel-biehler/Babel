//
// Created by max on 27/09/2021.
//

#ifndef BABEL_CONNECTIONWINDOW_HPP
#define BABEL_CONNECTIONWINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <Networking/Client.hpp>

namespace Babel {
    namespace Ui {
        class ConnectionWindow : public QWidget {
        public:
            explicit ConnectionWindow(Babel::Networking::Client *cli);

            ~ConnectionWindow();
        private:
            QStackedWidget _pages;
            QGridLayout *_layout;
        };
    }
}

#endif //BABEL_CONNECTIONWINDOW_HPP
