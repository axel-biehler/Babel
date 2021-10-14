#pragma once

#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <Networking/Client.hpp>

namespace Babel {
    namespace Ui {
        class AddFriendPage : public QWidget {
            Q_OBJECT
        public:
            AddFriendPage(Babel::Networking::Client *cli);

        private:
            QFormLayout _layout;
            QLineEdit _usernameLineEdit;
            QPushButton _addButton;
            Babel::Networking::Client *_cli;

        private slots:
            void addFriend();
            void onPacketReceived(Babel::Networking::RawPacket packet);
        };
    }
}