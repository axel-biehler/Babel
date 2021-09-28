#pragma once

#include <QScrollArea>

namespace Babel {
    namespace Ui {
        class FriendInvitesPage : public QWidget {
        public:
            FriendInvitesPage();

        private:
            QScrollArea _scrollArea;
            QVBoxLayout _mainLayout;
            QWidget _mainWidget;
            QVBoxLayout _innerLayout;
        };
    }
}

