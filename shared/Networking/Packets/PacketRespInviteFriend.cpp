#include "PacketRespInviteFriend.hpp"
#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Packets::PacketRespInviteFriend::PacketRespInviteFriend(char ok, const std::string &errorMessage, int friendshipId, const std::string &username)
        : Packet(PacketType::PacketRespInviteFriend), _ok(ok), _errorMessage(errorMessage), _friendshipId(friendshipId), _username(username) {
}

Babel::Networking::Packets::PacketRespInviteFriend::PacketRespInviteFriend(std::vector<char> data)
        : Packet(PacketType::PacketRespInviteFriend) {
    ArgumentsReader reader{data};
    _ok = reader.readChar();
    _errorMessage = reader.readString();
    _friendshipId = reader.readInt();
    _username = reader.readString();
}

char Babel::Networking::Packets::PacketRespInviteFriend::getOk() const {
    return _ok;
}

std::string Babel::Networking::Packets::PacketRespInviteFriend::getErrorMessage() const {
    return _errorMessage;
}

int Babel::Networking::Packets::PacketRespInviteFriend::getFriendshipId() const {
    return _friendshipId;
}

std::string Babel::Networking::Packets::PacketRespInviteFriend::getUsername() const {
    return _username;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespInviteFriend::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addChar(_ok);
    writer.addString(_errorMessage);
    writer.addInt(_friendshipId);
    writer.addString(_username);
    return {build(writer.build())};
}

