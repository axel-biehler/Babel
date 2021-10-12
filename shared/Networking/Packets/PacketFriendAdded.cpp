#include <Networking/Packets/PacketFriendAdded.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>

Babel::Networking::Packets::PacketFriendAdded::PacketFriendAdded(int id, const std::string &username)
    : Packet(PacketType::PacketFriendAdded), _id(id), _username(username) {
}

Babel::Networking::Packets::PacketFriendAdded::PacketFriendAdded(std::vector<char> data)
    : Packet(PacketType::PacketFriendAdded) {
    ArgumentsReader reader{data};
    _id = reader.readInt();
    _username = reader.readString();
}

std::string Babel::Networking::Packets::PacketFriendAdded::getUsername() const {
    return _username;
}

int Babel::Networking::Packets::PacketFriendAdded::getId() const {
    return _id;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketFriendAdded::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_id);
    writer.addString(_username);
    return {build(writer.build())};
}