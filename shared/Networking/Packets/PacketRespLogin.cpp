#include "PacketRespLogin.hpp"
#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Packets::PacketRespLogin::PacketRespLogin(char ok, const std::string &errorMessage, int userId)
    : Packet(PacketType::PacketRespLogin), _ok(ok), _errorMessage(errorMessage), _userId(userId) {
}

Babel::Networking::Packets::PacketRespLogin::PacketRespLogin(std::vector<char> data)
    : Packet(PacketType::PacketRespLogin) {
    ArgumentsReader reader{data};
    _ok = reader.readChar();
    _errorMessage = reader.readString();
    _userId = reader.readInt();
}

char Babel::Networking::Packets::PacketRespLogin::getOk() const {
    return _ok;
}

std::string Babel::Networking::Packets::PacketRespLogin::getErrorMessage() const {
    return _errorMessage;
}

int Babel::Networking::Packets::PacketRespLogin::getUserId() const {
    return _userId;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespLogin::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addChar(_ok);
    writer.addString(_errorMessage);
    writer.addInt(_userId);
    return {build(writer.build())};
}
