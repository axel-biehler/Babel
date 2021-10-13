#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <Networking/Client.hpp>

namespace Babel {
    namespace Ui {
        class FriendItemWidget : public QWidget {
        public:
            FriendItemWidget(Babel::Networking::Client *cli, int userId, const std::string &username);

        private:
            QHBoxLayout _mainLayout;
            QLabel _userImageLabel;
            QLabel _usernameLabel;
            QPushButton _messageButton;
            QPushButton _callButton;
            int _userId;
            std::string _username;
            Babel::Networking::Client *_cli;

        private slots:
            void call();
        };
    }
}

