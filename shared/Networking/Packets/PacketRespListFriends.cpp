#include <Networking/Packets/PacketRespListFriends.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketRespListFriends::PacketRespListFriends(std::vector<User> friends)
    : Packet(PacketType::PacketRespListFriends), _friends(friends) {
}

Babel::Networking::Packets::PacketRespListFriends::PacketRespListFriends(std::vector<char> data)
    : Packet(PacketType::PacketRespListFriends) {
    ArgumentsReader reader{data};
    auto count = reader.readInt();
    for (int i = 0; i < count; i++) {
        User u;
        u.id = reader.readInt();
        u.username = reader.readString();
        _friends.push_back(u);
    }
}

std::vector<Babel::Networking::User> Babel::Networking::Packets::PacketRespListFriends::getFriends() const {
    return _friends;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespListFriends::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_friends.size());
    for (auto &fri : _friends) {
        writer.addInt(fri.id);
        writer.addString(fri.username);
    }
    return {build(writer.build())};
}