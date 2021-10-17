#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <Networking/PacketTypes.hpp>
#include <Networking/Client.hpp>
#include "MessageWidget.hpp"

namespace Babel {
    namespace Ui {
        class ChatWidget : public QWidget {
            Q_OBJECT
        public:
            ChatWidget(const std::string &username, int id, Babel::Networking::Client *cli);
            ChatWidget(ChatWidget const &widget);

            void setUsername(std::string username);
            std::string getUsername() const;
            void setId(int id);
            int getUID() const;
            void setMessages(std::vector<Babel::Networking::Message> messages);
            void updateMessage(int uid);

        private:
            int _userId;
            std::string  _username;
            std::vector<Babel::Networking::Message> _messages;
            Babel::Networking::Client *_cli;

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

            std::vector<QWidget *> _widgets;

        private slots:
            void moveScrollBarToBottom(int min, int max);
            void sendMessage();

        };
    }
}


