#include <iostream>
#include "FriendItemWidget.hpp"

Babel::Ui::FriendItemWidget::FriendItemWidget(int userId, const std::string &username, std::shared_ptr<Babel::Ui::ChatWidget> chat) : _userId(userId),
                                                                                                         _chat(chat), _username(username) {
    setLayout(&_mainLayout);
    _mainLayout.setAlignment(Qt::AlignLeft);
    _mainLayout.addWidget(&_userImageLabel);
    _mainLayout.addWidget(&_usernameLabel);
    _mainLayout.addStretch(1);
    _mainLayout.addWidget(&_messageButton);
    _mainLayout.addWidget(&_callButton);

    _userImageLabel.setPixmap(QPixmap("images/avatar.png").scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    _messageButton.setIcon(QPixmap("images/avatar.png").scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    _messageButton.setIcon(QIcon("images/email.png"));
    _messageButton.setIconSize(QSize(24, 24));
    _messageButton.setFixedSize(24, 24);
    _messageButton.setFlat(true);
    _messageButton.setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    _callButton.setIcon(QIcon("images/phone.png"));
    _callButton.setIconSize(QSize(24, 24));
    _callButton.setFixedSize(24, 24);
    _callButton.setFlat(true);
    _callButton.setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    _usernameLabel.setText(username.c_str());
    _usernameLabel.setFont(QFont("Roboto", 10));
    connect(&_messageButton, &QPushButton::released, this, &FriendItemWidget::onMessageClick);
}

void Babel::Ui::FriendItemWidget::onMessageClick() {
    if (_chat != nullptr) {
        _chat->setId(_userId);
        _chat->setUsername(_username);
        std::cout << _userId << std::endl;
        _chat->updateMessage(_userId);
    }
}

QPushButton *Babel::Ui::FriendItemWidget::getMessageButton() {
    return &_messageButton;
}

