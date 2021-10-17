#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <Networking/Client.hpp>
#include "MainWindow.hpp"

namespace Babel {
    namespace Ui {
        class MainWindow;

        class FriendItemWidget : public QWidget {
        public:
            FriendItemWidget(Babel::Networking::Client *cli, int userId, const std::string &username, std::shared_ptr<ChatWidget> chat);

            QPushButton *getMessageButton();

        public slots:
            void onMessageClick();

        private:
            QHBoxLayout _mainLayout;
            QLabel _userImageLabel;
            QLabel _usernameLabel;
            QPushButton _messageButton;
            QPushButton _callButton;
            std::shared_ptr<ChatWidget> _chat;
            int _userId;
            std::string _username;
            Babel::Networking::Client *_cli;

        private slots:
            void call();
        };
    }
}

