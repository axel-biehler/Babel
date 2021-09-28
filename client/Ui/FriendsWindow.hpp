#pragma once

#include <QWidget>
#include <QTabWidget>

namespace Babel {
    namespace Ui {
        class FriendsWindow : public QWidget {
        public:
            FriendsWindow();

        private:
            QTabWidget _mainTabWidget;
        };
    }
}
