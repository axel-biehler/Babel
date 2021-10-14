#include <Networking/Packets/PacketCall.hpp>
#include "FriendItemWidget.hpp"
#include "CallWindow.hpp"

Babel::Ui::FriendItemWidget::FriendItemWidget(Babel::Networking::Client *cli, int userId, const std::string &username)
        : _cli(cli), _userId(userId), _username(username) {
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

    QObject::connect(&_callButton, &QPushButton::pressed, this, &FriendItemWidget::call);
}

void Babel::Ui::FriendItemWidget::call() {
    Networking::Packets::PacketCall packet{_userId};
    _cli->write(packet.serialize());
    (new CallWindow(_cli, CallStatus::WaitingForAnswer, _userId, _username))->show();
}