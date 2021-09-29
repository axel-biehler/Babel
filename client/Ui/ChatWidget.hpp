#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>

namespace Babel {
    namespace Ui {
        class ChatWidget : public QWidget {
        public:
            ChatWidget(const std::string &username, int id);

        private:
            int _userId;

            QVBoxLayout _mainLayout;

            QHBoxLayout _topLayout;
            QLabel _userImageLabel;
            QLabel _usernameLabel;
            QPushButton _callButton;

            QScrollArea _messagesScrollArea;

            QHBoxLayout _bottomLayout;
            QLineEdit _chatLineEdit;
            QPushButton _sendButton;
        };
    }
}


