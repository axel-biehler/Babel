//
// Created by max on 27/09/2021.
//

#ifndef BABEL_CONNECTIONWINDOW_HPP
#define BABEL_CONNECTIONWINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <Networking/Client.hpp>
#include <QTabWidget>
#include "ConnectionPage.hpp"

namespace Babel {
    namespace Ui {
        class ConnectionWindow : public QWidget {
            Q_OBJECT
        public:
            explicit ConnectionWindow(Babel::Networking::Client *cli);

            ~ConnectionWindow() = default;
        private:
            QVBoxLayout _layout;
            Babel::Ui::ConnectionPage _connectionPage;
        };
    }
}

#endif //BABEL_CONNECTIONWINDOW_HPP
