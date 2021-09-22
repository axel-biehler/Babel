#include <Networking/Packets/PacketCmdRegister.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCmdRegister::PacketCmdRegister(const std::string &username)
    : Packet(PacketType::PacketCmdRegister), _username(username) {
}

Babel::Networking::Packets::PacketCmdRegister::PacketCmdRegister(std::vector<char> data)
    : Packet(PacketType::PacketCmdRegister) {
    ArgumentsReader reader{data};
    _username = reader.readString();
}

std::string Babel::Networking::Packets::PacketCmdRegister::getUsername() const {
    return _username;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdRegister::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addString(_username);
    return {build(writer.build())};
}

