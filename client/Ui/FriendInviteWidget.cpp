#include <Networking/Packets/PacketCmdAcceptFriend.hpp>
#include <Networking/Packets/PacketRespAcceptFriend.hpp>
#include <Networking/Packets/PacketRespDenyFriend.hpp>
#include <iostream>
#include <Networking/Packets/PacketCmdDenyFriend.hpp>
#include <QMessageBox>
#include "FriendInviteWidget.hpp"

Babel::Ui::FriendInviteWidget::FriendInviteWidget(Babel::Networking::Client *cli, int friendshipId, const std::string &username, Babel::Ui::FriendInviteWidgetType type)
        : _cli(cli), _friendshipId(friendshipId) {
    setLayout(&_mainLayout);
    _mainLayout.addWidget(&_userImageLabel);
    _mainLayout.addSpacerItem(new QSpacerItem(8, 8));
    _mainLayout.addWidget(&_usernameLabel);
    _mainLayout.addStretch();

    if (type == Sent) {
        _mainLayout.addWidget(&_sentLabel);
        _mainLayout.addSpacerItem(new QSpacerItem(6, 6));
    } else {
        _mainLayout.addWidget(&_acceptButton);
        _mainLayout.addWidget(&_denyButton);
    }

    _userImageLabel.setPixmap(QPixmap("images/avatar.png").scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    _usernameLabel.setText(username.c_str());
    _usernameLabel.setFont(QFont("Roboto", 10));

    _sentLabel.setPixmap(QPixmap("images/sent.png").scaled(22, 22, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    _acceptButton.setIcon(QIcon("images/accept.png"));
    _acceptButton.setIconSize(QSize(32, 32));
    _acceptButton.setFixedSize(32, 32);
    _acceptButton.setFlat(true);
    _acceptButton.setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    _denyButton.setIcon(QIcon("images/deny.png"));
    _denyButton.setIconSize(QSize(32, 32));
    _denyButton.setFixedSize(32, 32);
    _denyButton.setFlat(true);
    _denyButton.setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    QObject::connect(&_acceptButton, &QPushButton::pressed, this, &FriendInviteWidget::acceptInvite);
    QObject::connect(&_denyButton, &QPushButton::pressed, this, &FriendInviteWidget::denyInvite);
    QObject::connect(_cli, &Babel::Networking::Client::packetReceive, this, &FriendInviteWidget::onPacketReceived);
}

void Babel::Ui::FriendInviteWidget::acceptInvite() {
    Babel::Networking::Packets::PacketCmdAcceptFriend packet{_friendshipId};
    _cli->write(packet.serialize());
}

void Babel::Ui::FriendInviteWidget::denyInvite() {
    Babel::Networking::Packets::PacketCmdDenyFriend packet{_friendshipId};
    _cli->write(packet.serialize());
}

void Babel::Ui::FriendInviteWidget::onPacketReceived(Babel::Networking::RawPacket rawPacket) {
    if (rawPacket.getPacketType() == Networking::PacketRespAcceptFriend) {
        auto packet = std::static_pointer_cast<Babel::Networking::Packets::PacketRespAcceptFriend>(rawPacket.deserialize());
        if (packet->getFriendshipId() != _friendshipId)
            return;

        if (packet->getOk() == 1) {
            QMessageBox::information(this, "Invitation accepted.", "The invitation was accepted.");
            delete this;
        } else {
            QMessageBox::critical(this, "Could not accept invitation.", packet->getErrorMessage().c_str());
        }
    } else if (rawPacket.getPacketType() == Networking::PacketRespDenyFriend) {
        auto packet = std::static_pointer_cast<Babel::Networking::Packets::PacketRespDenyFriend>(rawPacket.deserialize());
        if (packet->getFriendshipId() != _friendshipId)
            return;
        if (packet->getOk() == 1) {
            QMessageBox::information(this, "Invitation denied.", "The invitation was denied.");
            delete this;
        } else {
            QMessageBox::critical(this, "Could not deny invitation.", packet->getErrorMessage().c_str());
        }
    }
}
