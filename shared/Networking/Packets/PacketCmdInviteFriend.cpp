#include <Networking/Packets/PacketCmdInviteFriend.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCmdInviteFriend::PacketCmdInviteFriend(const std::string &username)
    : Packet(PacketType::PacketCmdInviteFriend), _username(username) {
}

Babel::Networking::Packets::PacketCmdInviteFriend::PacketCmdInviteFriend(std::vector<char> data)
    : Packet(PacketType::PacketCmdInviteFriend) {
    ArgumentsReader reader{data};
    _username = reader.readString();
}

std::string Babel::Networking::Packets::PacketCmdInviteFriend::getUsername() const {
    return _username;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdInviteFriend::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addString(_username);
    return {build(writer.build())};
}