#include <QLabel>
#include <Networking/Packets/PacketCmdListFriends.hpp>
#include <Networking/Packets/PacketRespListFriends.hpp>
#include <Networking/Packets/PacketRespAcceptFriend.hpp>
#include <Networking/Packets/PacketInviteReceived.hpp>
#include <QMessageBox>
#include "MainWindow.hpp"
#include "FriendsWindow.hpp"
#include "FriendItemWidget.hpp"

Babel::Ui::MainWindow::MainWindow(Babel::Networking::Client *cli) : _cli(cli) {
    setWindowTitle("Babel");
    setMinimumSize(800, 600);
    setLayout(&_mainLayout);

    _chatWidget = std::make_shared<Babel::Ui::ChatWidget>("John", 4);

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

    _mainLayout.addWidget(_chatWidget.get(), 1);

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
        for (auto &f : resp->getFriends()) {
            _friendsInnerLayout.addWidget(new FriendItemWidget(f.id, f.username));
        }
    } else if (packet.getPacketType() == Networking::PacketRespAcceptFriend) {
        auto resp = std::static_pointer_cast<Babel::Networking::Packets::PacketRespAcceptFriend>(packet.deserialize());
        if (resp->getOk() == 0)
            return;
        _friendsInnerLayout.addWidget(new FriendItemWidget(resp->getUserId(), resp->getUsername()));
    } else if (packet.getPacketType() == Networking::PacketInviteReceived) {
        auto resp = std::static_pointer_cast<Babel::Networking::Packets::PacketInviteReceived>(packet.deserialize());
        QMessageBox::information(nullptr, "Friend invite received", QString("You received an invite from ") + QString(resp->getUsername().c_str()) + QString("."));
    }
}
