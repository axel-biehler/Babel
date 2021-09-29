#include "ChatWidget.hpp"

Babel::Ui::ChatWidget::ChatWidget(const std::string &username, int id) : _userId(id) {
    setLayout(&_mainLayout);

    _mainLayout.addLayout(&_topLayout);
    _userImageLabel.setPixmap(QPixmap("images/avatar.png").scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    _topLayout.addWidget(&_userImageLabel);
    _usernameLabel.setText(username.c_str());
    _usernameLabel.setFont(QFont("Roboto", 16));
    _topLayout.addSpacerItem(new QSpacerItem(4, 4));
    _topLayout.addWidget(&_usernameLabel);
    _topLayout.addStretch(1);
    _callButton.setIcon(QIcon("images/phone.png"));
    _callButton.setIconSize(QSize(20, 20));
    _callButton.setFixedSize(32, 32);
    _callButton.setFlat(true);
    _callButton.setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    _topLayout.addWidget(&_callButton);

    _mainLayout.addSpacerItem(new QSpacerItem(10, 8));
    _mainLayout.addWidget(&_messagesScrollArea, 1);

    _mainLayout.addLayout(&_bottomLayout);
    _chatLineEdit.setPlaceholderText("Your message...");
    _chatLineEdit.setFixedHeight(32);
    _chatLineEdit.setFont(QFont("Roboto", 12));
    _bottomLayout.addWidget(&_chatLineEdit, 1);
    _sendButton.setIcon(QIcon("images/sent.png"));
    _sendButton.setIconSize(QSize(20, 20));
    _sendButton.setFixedSize(32, 32);
    _sendButton.setFlat(true);
    _sendButton.setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    _bottomLayout.addWidget(&_sendButton);
}
