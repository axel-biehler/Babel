#pragma once

#include <QWidget>
#include <QTabWidget>
#include <Networking/Client.hpp>

namespace Babel {
    namespace Ui {
        class FriendsWindow : public QWidget {
        public:
            FriendsWindow(Babel::Networking::Client *cli);

        private:
            QTabWidget _mainTabWidget;
            Babel::Networking::Client *_cli;
        };
    }
}
