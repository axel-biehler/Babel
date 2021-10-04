#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace Babel {
    namespace Ui {
        enum FriendInviteWidgetType {
            Sent,
            Received
        };

        class FriendInviteWidget : public QWidget {
        public:
            FriendInviteWidget(const std::string &username, FriendInviteWidgetType type);

        private:
            QHBoxLayout _mainLayout;
            QLabel _userImageLabel;
            QLabel _usernameLabel;
            QLabel _sentLabel;
            QPushButton _acceptButton;
            QPushButton _denyButton;
        };
    }
}

