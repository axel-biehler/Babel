#include <Networking/Packets/PacketCmdRegister.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCmdRegister::PacketCmdRegister(const std::string &username, const std::string &password)
    : Packet(PacketType::PacketCmdRegister), _username(username), _password(password) {
}

Babel::Networking::Packets::PacketCmdRegister::PacketCmdRegister(std::vector<char> data)
    : Packet(PacketType::PacketCmdRegister) {
    ArgumentsReader reader{data};
    _username = reader.readString();
    _password = reader.readString();
}

std::string Babel::Networking::Packets::PacketCmdRegister::getUsername() const {
    return _username;
}

std::string Babel::Networking::Packets::PacketCmdRegister::getPassword() const {
    return _password;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdRegister::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addString(_username);
    writer.addString(_password);
    return {build(writer.build())};
}

