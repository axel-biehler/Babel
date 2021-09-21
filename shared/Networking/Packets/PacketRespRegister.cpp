#include "PacketRespRegister.hpp"
#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Packets::PacketRespRegister::PacketRespRegister(char ok, const std::string &errorMessage)
    : Packet(PacketType::PacketRespRegister), _ok(ok), _errorMessage(errorMessage) {
}

Babel::Networking::Packets::PacketRespRegister::PacketRespRegister(std::vector<char> data)
    : Packet(PacketType::PacketRespRegister) {
    ArgumentsReader reader{data};
    _ok = reader.readChar();
    _errorMessage = reader.readString();
}

char Babel::Networking::Packets::PacketRespRegister::getOk() const {
    return _ok;
}

std::string Babel::Networking::Packets::PacketRespRegister::getErrorMessage() const {
    return _errorMessage;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespRegister::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addChar(_ok);
    writer.addString(_errorMessage);
    return {build(writer.build())};
}

