#include <Networking/Packets/PacketFriendAdded.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>

Babel::Networking::Packets::PacketFriendAdded::PacketFriendAdded(int id, const std::string &username, int friendshipId)
    : Packet(PacketType::PacketFriendAdded), _id(id), _username(username), _friendshipId(friendshipId) {
}

Babel::Networking::Packets::PacketFriendAdded::PacketFriendAdded(std::vector<char> data)
    : Packet(PacketType::PacketFriendAdded) {
    ArgumentsReader reader{data};
    _id = reader.readInt();
    _username = reader.readString();
    _friendshipId = reader.readInt();
}

std::string Babel::Networking::Packets::PacketFriendAdded::getUsername() const {
    return _username;
}

int Babel::Networking::Packets::PacketFriendAdded::getId() const {
    return _id;
}

int Babel::Networking::Packets::PacketFriendAdded::getFriendshipId() const {
    return _friendshipId;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketFriendAdded::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_id);
    writer.addString(_username);
    writer.addInt(_friendshipId);
    return {build(writer.build())};
}