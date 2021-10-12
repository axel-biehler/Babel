#include <Networking/Packets/PacketCmdInviteFriend.hpp>
#include <Networking/Packets/PacketRespInviteFriend.hpp>
#include <iostream>
#include <QMessageBox>
#include "AddFriendPage.hpp"

Babel::Ui::AddFriendPage::AddFriendPage(Babel::Networking::Client *cli) : _cli(cli) {
    _usernameLineEdit.setPlaceholderText("Username");
    _usernameLineEdit.setFixedHeight(28);
    _usernameLineEdit.setFont(QFont("Roboto", 10));
    _addButton.setFont(QFont("Roboto", 10));
    _addButton.setText("Add");

    _layout.addRow("Username:", &_usernameLineEdit);
    _layout.addRow("", &_addButton);
    _layout.setSpacing(10);
    setLayout(&_layout);

    QObject::connect(&_addButton, &QPushButton::pressed, this, &AddFriendPage::addFriend);
    QObject::connect(_cli, &Networking::Client::packetReceive, this, &AddFriendPage::onPacketReceived);
}

void Babel::Ui::AddFriendPage::addFriend() {
    auto username = _usernameLineEdit.text().toStdString();
    Networking::Packets::PacketCmdInviteFriend packet{username};
    _cli->write(packet.serialize());
}

void Babel::Ui::AddFriendPage::onPacketReceived(Babel::Networking::RawPacket packet) {
    if (packet.getPacketType() != Networking::PacketRespInviteFriend)
        return;

    auto resp = std::static_pointer_cast<Networking::Packets::PacketRespInviteFriend>(packet.deserialize());
    if (resp->getOk() == 1) {
        QMessageBox::information(this, "Invitation sent.", "Your invitation was sent!");
    } else {
        QMessageBox::critical(this, "Could not add friend.", resp->getErrorMessage().c_str());
    }
}
