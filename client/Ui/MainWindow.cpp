#include <QLabel>
#include <Networking/Packets/PacketCmdListFriends.hpp>
#include <Networking/Packets/PacketRespListFriends.hpp>
#include <Networking/Packets/PacketRespAcceptFriend.hpp>
#include <Networking/Packets/PacketInviteReceived.hpp>
#include <Networking/Packets/PacketRespListMessages.hpp>
#include <QMessageBox>
#include <Networking/Packets/PacketFriendAdded.hpp>
#include <Networking/Packets/PacketCallReceived.hpp>
#include <iostream>
#include <Networking/Packets/PacketCmdListMessages.hpp>
#include "MainWindow.hpp"
#include "FriendsWindow.hpp"
#include "FriendItemWidget.hpp"
#include "CallWindow.hpp"

Babel::Ui::MainWindow::MainWindow(Babel::Networking::Client *cli) : _cli(cli), _chatWidget(nullptr), _firstId(-1), _firstUsername("") {
    setWindowTitle("Babel");
    setMinimumSize(800, 600);
    setLayout(&_mainLayout);

    _mainLayout.addWidget(&_leftWidget);
    _leftWidget.setFixedWidth(250);
    _leftWidget.setLayout(&_leftLayout);
    _leftLayout.addWidget(&_friendsScrollArea, 1);
    _friendsScrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _friendsScrollArea.setWidgetResizable(true);
    _friendsScrollArea.setParent(&_leftWidget);
    _friendsScrollArea.setWidget(&_friendsContainer);
    _friendsContainer.setLayout(&_friendsInnerLayout);
    _friendsInnerLayout.setAlignment(Qt::AlignTop);
    _leftLayout.addWidget(&_friendsButton);

    _friendsButton.setText("Manage friends");
    _friendsButton.setFont(QFont("Roboto", 10));
    _friendsButton.setFixedHeight(32);

    connect(&_friendsButton, &QPushButton::released, this, &MainWindow::showFriends);
    connect(_cli, &Babel::Networking::Client::packetReceive, this, &MainWindow::onPacketReceived);

    Babel::Networking::Packets::PacketCmdListFriends friends;
    _cli->write(friends.serialize());
}

void Babel::Ui::MainWindow::showFriends() {
    (new FriendsWindow(_cli))->show();
}

void Babel::Ui::MainWindow::onPacketReceived(Babel::Networking::RawPacket packet) {
    if (packet.getPacketType() == Networking::PacketType::PacketRespListFriends) {
        auto resp = std::static_pointer_cast<Networking::Packets::PacketRespListFriends>(packet.deserialize());
        if (!resp->getFriends().empty()) {
            _firstUsername = resp->getFriends()[0].username;
            _firstId = resp->getFriends()[0].id;
        }
        if (!_chatWidget) {
            _chatWidget = std::make_shared<Babel::Ui::ChatWidget>(_firstUsername.c_str(), _firstId, _cli);
            _mainLayout.addWidget(_chatWidget.get(), 1);
        }
        for (auto &f : resp->getFriends()) {
            auto *friendItem = new FriendItemWidget(_cli, f.id, f.username, _chatWidget);
            _friendsInnerLayout.addWidget(friendItem);
            connect(friendItem->getMessageButton(), &QPushButton::released, friendItem, &FriendItemWidget::onMessageClick);
        }
    } else if (packet.getPacketType() == Networking::PacketRespAcceptFriend) {
        auto resp = std::static_pointer_cast<Babel::Networking::Packets::PacketRespAcceptFriend>(packet.deserialize());
        if (resp->getOk() == 0)
            return;
        _friendsInnerLayout.addWidget(new FriendItemWidget(_cli, resp->getUserId(), resp->getUsername(), _chatWidget));
    } else if (packet.getPacketType() == Networking::PacketInviteReceived) {
        auto resp = std::static_pointer_cast<Babel::Networking::Packets::PacketInviteReceived>(packet.deserialize());
        QMessageBox::information(nullptr, "Friend invite received", QString("You received an invite from ") + QString(resp->getUsername().c_str()) + QString("."));
    } else if (packet.getPacketType() == Networking::PacketFriendAdded) {
        auto resp = std::static_pointer_cast<Babel::Networking::Packets::PacketFriendAdded>(packet.deserialize());
        _friendsInnerLayout.addWidget(new FriendItemWidget(_cli, resp->getId(), resp->getUsername(), _chatWidget));
    } else if (packet.getPacketType() == Networking::PacketCallReceived) {
        auto resp = std::static_pointer_cast<Babel::Networking::Packets::PacketCallReceived>(packet.deserialize());
        (new Babel::Ui::CallWindow(_cli, Babel::Ui::CallStatus::Receiving, resp->getId(), resp->getUsername()))->show();
    }
    if (packet.getPacketType() == Networking::PacketRespListMessages) {
        auto resp = std::static_pointer_cast<Babel::Networking::Packets::PacketRespListMessages>(packet.deserialize());
        auto message = resp->getMessages();
        _chatWidget->setMessages(resp->getMessages());
        _chatWidget->updateMessage(_chatWidget->getUID());
    }
}
