#include <QVBoxLayout>
#include <Networking/Packets/PacketCmdListInvites.hpp>
#include <Networking/Packets/PacketRespListInvites.hpp>
#include "FriendInvitesPage.hpp"
#include "FriendInviteWidget.hpp"

Babel::Ui::FriendInvitesPage::FriendInvitesPage(Babel::Networking::Client *cli) : _cli(cli) {
    setLayout(&_mainLayout);
    _scrollArea.setParent(this);
    _mainLayout.addWidget(&_scrollArea);
    _scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _scrollArea.setWidgetResizable(true);
    _scrollArea.setWidget(&_mainWidget);
    _innerLayout.setAlignment(Qt::AlignTop);
    _mainWidget.setLayout(&_innerLayout);

    /*
    for (int i = 0; i < 50; i++) {
        FriendInviteWidget *w = new FriendInviteWidget("John Doe", i % 2 == 0 ? Sent : Received);
        _innerLayout.addWidget(w);
    }
    */

    QObject::connect(_cli, &Babel::Networking::Client::packetReceive, this, &FriendInvitesPage::onPacketReceived);

    Networking::Packets::PacketCmdListInvites packet;
    _cli->write(packet.serialize());
}

void Babel::Ui::FriendInvitesPage::onPacketReceived(Babel::Networking::RawPacket packet) {
    if (packet.getPacketType() == Networking::PacketRespListInvites) {
        auto resp = std::static_pointer_cast<Networking::Packets::PacketRespListInvites>(packet.deserialize());
        for (auto invite : resp->getInvites()) {
            if (invite.from == _cli->getUserId()) {
                auto w = new FriendInviteWidget(invite.toUsername, Sent);
                _innerLayout.addWidget(w);
            } else {
                auto w = new FriendInviteWidget(invite.fromUsername, Received);
                _innerLayout.addWidget(w);
            }
        }
    }
}
