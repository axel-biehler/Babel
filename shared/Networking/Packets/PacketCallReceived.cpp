#include <Networking/Packets/PacketCallReceived.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCallReceived::PacketCallReceived(int id, const std::string &username)
    : Packet(PacketType::PacketCallReceived), _id(id), _username(username) {
}

Babel::Networking::Packets::PacketCallReceived::PacketCallReceived(std::vector<char> data)
    : Packet(PacketType::PacketCallReceived) {
    ArgumentsReader reader{data};
    _id = reader.readInt();
    _username = reader.readString();
}

int Babel::Networking::Packets::PacketCallReceived::getId() const {
    return _id;
}

std::string Babel::Networking::Packets::PacketCallReceived::getUsername() const {
    return _username;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCallReceived::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_id);
    writer.addString(_username);
    return {build(writer.build())};
}