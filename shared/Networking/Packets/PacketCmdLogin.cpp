#include <Networking/Packets/PacketCmdLogin.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCmdLogin::PacketCmdLogin(const std::string &username)
    : Packet(PacketType::PacketCmdLogin), _username(username) {
}

Babel::Networking::Packets::PacketCmdLogin::PacketCmdLogin(std::vector<char> data)
    : Packet(PacketType::PacketCmdLogin) {
    ArgumentsReader reader{data};
    _username = reader.readString();
}

std::string Babel::Networking::Packets::PacketCmdLogin::getUsername() const {
    return _username;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdLogin::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addString(_username);
    return {build(writer.build())};
}