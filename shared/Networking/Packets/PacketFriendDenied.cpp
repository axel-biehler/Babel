#include <Networking/Packets/PacketFriendDenied.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>

Babel::Networking::Packets::PacketFriendDenied::PacketFriendDenied(int id)
    : Packet(PacketType::PacketFriendDenied), _id(id) {
}

Babel::Networking::Packets::PacketFriendDenied::PacketFriendDenied(std::vector<char> data)
    : Packet(PacketType::PacketFriendDenied) {
    ArgumentsReader reader{data};
    _id = reader.readInt();
}

int Babel::Networking::Packets::PacketFriendDenied::getId() const {
    return _id;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketFriendDenied::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_id);
    return {build(writer.build())};
}