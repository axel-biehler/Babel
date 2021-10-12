#include <Networking/Packets/PacketInviteReceived.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketInviteReceived::PacketInviteReceived(int id, const std::string &username)
    : Packet(PacketType::PacketInviteReceived), _id(id), _username(username) {
}

Babel::Networking::Packets::PacketInviteReceived::PacketInviteReceived(std::vector<char> data)
    : Packet(PacketType::PacketInviteReceived) {
    ArgumentsReader reader{data};
    _id = reader.readInt();
    _username = reader.readString();
}

int Babel::Networking::Packets::PacketInviteReceived::getId() const {
    return _id;
}

std::string Babel::Networking::Packets::PacketInviteReceived::getUsername() const {
    return _username;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketInviteReceived::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_id);
    writer.addString(_username);
    return {build(writer.build())};
}