#include "PacketRespDenyFriend.hpp"
#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Packets::PacketRespDenyFriend::PacketRespDenyFriend(char ok, const std::string &errorMessage)
        : Packet(PacketType::PacketRespDenyFriend), _ok(ok), _errorMessage(errorMessage) {
}

Babel::Networking::Packets::PacketRespDenyFriend::PacketRespDenyFriend(std::vector<char> data)
        : Packet(PacketType::PacketRespDenyFriend) {
    ArgumentsReader reader{data};
    _ok = reader.readChar();
    _errorMessage = reader.readString();
}

char Babel::Networking::Packets::PacketRespDenyFriend::getOk() const {
    return _ok;
}

std::string Babel::Networking::Packets::PacketRespDenyFriend::getErrorMessage() const {
    return _errorMessage;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespDenyFriend::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addChar(_ok);
    writer.addString(_errorMessage);
    return {build(writer.build())};
}

