#include <Networking/RawPacket.hpp>
#include <memory>
#include <Networking/Packets/PacketCmdRegister.hpp>
#include <Networking/Packets/PacketRespRegister.hpp>
#include <Networking/Packets/PacketCmdLogin.hpp>
#include <Networking/Packets/PacketRespLogin.hpp>
#include <Networking/Packets/PacketCmdLogout.hpp>
#include <Networking/Packets/PacketAudio.hpp>
#include <Networking/Packets/PacketCmdInviteFriend.hpp>
#include <Networking/Packets/PacketRespInviteFriend.hpp>
#include <Networking/Packets/PacketCmdAcceptFriend.hpp>
#include <Networking/Packets/PacketRespAcceptFriend.hpp>
#include <Networking/Packets/PacketCmdDenyFriend.hpp>
#include <Networking/Packets/PacketRespDenyFriend.hpp>
#include <Networking/Packets/PacketInviteReceived.hpp>
#include <Networking/Packets/PacketFriendAdded.hpp>
#include <Networking/Packets/PacketFriendDenied.hpp>
#include <Networking/Packets/PacketCmdListFriends.hpp>
#include <Networking/Packets/PacketRespListFriends.hpp>
#include <Networking/Packets/PacketCmdListInvites.hpp>
#include <Networking/Packets/PacketRespListInvites.hpp>

Babel::Networking::RawPacket::RawPacket(std::vector<char> data) : _data(data) {
}

Babel::Networking::RawPacket::RawPacket(const Babel::Networking::RawPacket &other) : _data(other._data) {
}

Babel::Networking::RawPacket &Babel::Networking::RawPacket::operator=(const Babel::Networking::RawPacket &other) {
    _data = other._data;
    return *this;
}

std::shared_ptr<Babel::Networking::Packet> Babel::Networking::RawPacket::deserialize() {
    if (getPacketType() == PacketUnknown)
        return std::make_shared<Babel::Networking::Packet>(PacketUnknown);

    switch (getPacketType()) {
        case PacketCmdRegister: return std::make_shared<Packets::PacketCmdRegister>(_data);
        case PacketRespRegister: return std::make_shared<Packets::PacketRespRegister>(_data);
        case PacketCmdLogin: return std::make_shared<Packets::PacketCmdLogin>(_data);
        case PacketRespLogin: return std::make_shared<Packets::PacketRespLogin>(_data);
        case PacketCmdLogout: return std::make_shared<Packets::PacketCmdLogout>(_data);
        case PacketAudio: return std::make_shared<Packets::PacketAudio>(_data);
        case PacketCmdInviteFriend: return std::make_shared<Packets::PacketCmdInviteFriend>(_data);
        case PacketRespInviteFriend: return std::make_shared<Packets::PacketRespInviteFriend>(_data);
        case PacketCmdAcceptFriend: return std::make_shared<Packets::PacketCmdAcceptFriend>(_data);
        case PacketRespAcceptFriend: return std::make_shared<Packets::PacketRespAcceptFriend>(_data);
        case PacketCmdDenyFriend: return std::make_shared<Packets::PacketCmdDenyFriend>(_data);
        case PacketRespDenyFriend: return std::make_shared<Packets::PacketRespDenyFriend>(_data);
        case PacketInviteReceived: return std::make_shared<Packets::PacketInviteReceived>(_data);
        case PacketFriendAdded: return std::make_shared<Packets::PacketFriendAdded>(_data);
        case PacketFriendDenied: return std::make_shared<Packets::PacketFriendDenied>(_data);
        case PacketCmdListFriends: return std::make_shared<Packets::PacketCmdListFriends>(_data);
        case PacketRespListFriends: return std::make_shared<Packets::PacketRespListFriends>(_data);
        case PacketCmdListInvites: return std::make_shared<Packets::PacketCmdListInvites>(_data);
        case PacketRespListInvites: return std::make_shared<Packets::PacketRespListInvites>(_data);
        default: return std::make_shared<Babel::Networking::Packet>(PacketUnknown);
    }
}

Babel::Networking::PacketType Babel::Networking::RawPacket::getPacketType() const {
    if (_data.size() < sizeof(int) + sizeof(char))
        return PacketUnknown;
    return static_cast<PacketType>(_data[4]);
}

const std::vector<char> Babel::Networking::RawPacket::getData() const {
    return _data;
}

const std::string Babel::Networking::RawPacket::toStdString() const {
    std::string str = "";

    for (int i = 0; i < _data.size(); i++)
        str.push_back(_data[i]);
    return str;
}
