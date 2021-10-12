#pragma once

#include <QScrollArea>
#include <Networking/Client.hpp>

namespace Babel {
    namespace Ui {
        class FriendInvitesPage : public QWidget {
        public:
            FriendInvitesPage(Babel::Networking::Client *cli);

        private:
            QScrollArea _scrollArea;
            QVBoxLayout _mainLayout;
            QWidget _mainWidget;
            QVBoxLayout _innerLayout;
            Babel::Networking::Client *_cli;

        private slots:
            void onPacketReceived(Babel::Networking::RawPacket packet);
        };
    }
}

