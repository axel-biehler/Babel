#include <Networking/Packets/PacketCmdLogin.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCmdLogin::PacketCmdLogin(const std::string &username, const std::string &password)
    : Packet(PacketType::PacketCmdLogin), _username(username), _password(password) {
}

Babel::Networking::Packets::PacketCmdLogin::PacketCmdLogin(std::vector<char> data)
    : Packet(PacketType::PacketCmdLogin) {
    ArgumentsReader reader{data};
    _username = reader.readString();
    _password = reader.readString();
}

std::string Babel::Networking::Packets::PacketCmdLogin::getUsername() const {
    return _username;
}

std::string Babel::Networking::Packets::PacketCmdLogin::getPassword() const {
    return _password;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdLogin::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addString(_username);
    writer.addString(_password);
    return {build(writer.build())};
}

