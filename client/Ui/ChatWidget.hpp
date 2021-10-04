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
            Q_OBJECT
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
            QWidget _innerChat;
            QWidget _outerChat;
            QVBoxLayout _innerLayout;
            QVBoxLayout _outerLayout;

            QHBoxLayout _bottomLayout;
            QLineEdit _chatLineEdit;
            QPushButton _sendButton;

        private slots:
            void moveScrollBarToBottom(int min, int max);
        };
    }
}


