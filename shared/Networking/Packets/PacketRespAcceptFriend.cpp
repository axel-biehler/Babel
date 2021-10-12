#include "PacketRespAcceptFriend.hpp"
#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Packets::PacketRespAcceptFriend::PacketRespAcceptFriend(char ok, const std::string &errorMessage, int friendshipId, int userId, const std::string &username)
        : Packet(PacketType::PacketRespAcceptFriend), _ok(ok), _errorMessage(errorMessage), _friendshipId(friendshipId), _userId(userId), _username(username) {
}

Babel::Networking::Packets::PacketRespAcceptFriend::PacketRespAcceptFriend(std::vector<char> data)
        : Packet(PacketType::PacketRespAcceptFriend) {
    ArgumentsReader reader{data};
    _ok = reader.readChar();
    _errorMessage = reader.readString();
    _friendshipId = reader.readInt();
    _userId = reader.readInt();
    _username = reader.readString();
}

char Babel::Networking::Packets::PacketRespAcceptFriend::getOk() const {
    return _ok;
}

std::string Babel::Networking::Packets::PacketRespAcceptFriend::getErrorMessage() const {
    return _errorMessage;
}

int Babel::Networking::Packets::PacketRespAcceptFriend::getFriendshipId() const {
    return _friendshipId;
}

int Babel::Networking::Packets::PacketRespAcceptFriend::getUserId() const {
    return _userId;
}

std::string Babel::Networking::Packets::PacketRespAcceptFriend::getUsername() const {
    return _username;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespAcceptFriend::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addChar(_ok);
    writer.addString(_errorMessage);
    writer.addInt(_friendshipId);
    writer.addInt(_userId);
    writer.addString(_username);
    return {build(writer.build())};
}

