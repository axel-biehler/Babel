#include "PacketRespDenyFriend.hpp"
#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Packets::PacketRespDenyFriend::PacketRespDenyFriend(char ok, const std::string &errorMessage, int friendshipId)
        : Packet(PacketType::PacketRespDenyFriend), _ok(ok), _errorMessage(errorMessage), _friendshipId(friendshipId) {
}

Babel::Networking::Packets::PacketRespDenyFriend::PacketRespDenyFriend(std::vector<char> data)
        : Packet(PacketType::PacketRespDenyFriend) {
    ArgumentsReader reader{data};
    _ok = reader.readChar();
    _errorMessage = reader.readString();
    _friendshipId = reader.readInt();
}

char Babel::Networking::Packets::PacketRespDenyFriend::getOk() const {
    return _ok;
}

std::string Babel::Networking::Packets::PacketRespDenyFriend::getErrorMessage() const {
    return _errorMessage;
}

int Babel::Networking::Packets::PacketRespDenyFriend::getFriendshipId() const {
    return _friendshipId;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespDenyFriend::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addChar(_ok);
    writer.addString(_errorMessage);
    writer.addInt(_friendshipId);
    return {build(writer.build())};
}

