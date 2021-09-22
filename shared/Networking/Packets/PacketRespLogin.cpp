#include "PacketRespLogin.hpp"
#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Packets::PacketRespLogin::PacketRespLogin(char ok, const std::string &errorMessage)
    : Packet(PacketType::PacketRespLogin), _ok(ok), _errorMessage(errorMessage) {
}

Babel::Networking::Packets::PacketRespLogin::PacketRespLogin(std::vector<char> data)
    : Packet(PacketType::PacketRespLogin) {
    ArgumentsReader reader{data};
    _ok = reader.readChar();
    _errorMessage = reader.readString();
}

char Babel::Networking::Packets::PacketRespLogin::getOk() const {
    return _ok;
}

std::string Babel::Networking::Packets::PacketRespLogin::getErrorMessage() const {
    return _errorMessage;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespLogin::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addChar(_ok);
    writer.addString(_errorMessage);
    return {build(writer.build())};
}

