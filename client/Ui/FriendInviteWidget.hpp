#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <Networking/Client.hpp>

namespace Babel {
    namespace Ui {
        enum FriendInviteWidgetType {
            Sent,
            Received
        };

        class FriendInviteWidget : public QWidget {
        public:
            FriendInviteWidget(Babel::Networking::Client *cli, int friendshipId, const std::string &username, FriendInviteWidgetType type);

        private:
            Babel::Networking::Client *_cli;
            int _friendshipId;
            QHBoxLayout _mainLayout;
            QLabel _userImageLabel;
            QLabel _usernameLabel;
            QLabel _sentLabel;
            QPushButton _acceptButton;
            QPushButton _denyButton;

        private slots:
            void acceptInvite();
            void denyInvite();
            void onPacketReceived(Babel::Networking::RawPacket packet);
        };
    }
}

