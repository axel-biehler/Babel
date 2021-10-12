#include "PacketRespAcceptFriend.hpp"
#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Packets::PacketRespAcceptFriend::PacketRespAcceptFriend(char ok, const std::string &errorMessage)
        : Packet(PacketType::PacketRespAcceptFriend), _ok(ok), _errorMessage(errorMessage) {
}

Babel::Networking::Packets::PacketRespAcceptFriend::PacketRespAcceptFriend(std::vector<char> data)
        : Packet(PacketType::PacketRespAcceptFriend) {
    ArgumentsReader reader{data};
    _ok = reader.readChar();
    _errorMessage = reader.readString();
}

char Babel::Networking::Packets::PacketRespAcceptFriend::getOk() const {
    return _ok;
}

std::string Babel::Networking::Packets::PacketRespAcceptFriend::getErrorMessage() const {
    return _errorMessage;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespAcceptFriend::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addChar(_ok);
    writer.addString(_errorMessage);
    return {build(writer.build())};
}

