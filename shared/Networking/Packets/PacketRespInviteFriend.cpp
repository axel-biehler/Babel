#include "PacketRespInviteFriend.hpp"
#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Packets::PacketRespInviteFriend::PacketRespInviteFriend(char ok, const std::string &errorMessage)
        : Packet(PacketType::PacketRespInviteFriend), _ok(ok), _errorMessage(errorMessage) {
}

Babel::Networking::Packets::PacketRespInviteFriend::PacketRespInviteFriend(std::vector<char> data)
        : Packet(PacketType::PacketRespInviteFriend) {
    ArgumentsReader reader{data};
    _ok = reader.readChar();
    _errorMessage = reader.readString();
}

char Babel::Networking::Packets::PacketRespInviteFriend::getOk() const {
    return _ok;
}

std::string Babel::Networking::Packets::PacketRespInviteFriend::getErrorMessage() const {
    return _errorMessage;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespInviteFriend::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addChar(_ok);
    writer.addString(_errorMessage);
    return {build(writer.build())};
}

