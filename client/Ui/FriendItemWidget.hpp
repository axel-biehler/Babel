#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace Babel {
    namespace Ui {
        class FriendItemWidget : public QWidget {
        public:
            FriendItemWidget(int userId, const std::string &username);

        private:
            QHBoxLayout _mainLayout;
            QLabel _userImageLabel;
            QLabel _usernameLabel;
            QPushButton _messageButton;
            QPushButton _callButton;
            int _userId;
        };
    }
}

