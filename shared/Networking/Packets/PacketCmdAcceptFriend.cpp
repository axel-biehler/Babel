#include <Networking/Packets/PacketCmdAcceptFriend.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCmdAcceptFriend::PacketCmdAcceptFriend(int id)
    : Packet(PacketType::PacketCmdAcceptFriend), _id(id) {
}

Babel::Networking::Packets::PacketCmdAcceptFriend::PacketCmdAcceptFriend(std::vector<char> data)
    : Packet(PacketType::PacketCmdAcceptFriend) {
    ArgumentsReader reader{data};
    _id = reader.readInt();
}

int Babel::Networking::Packets::PacketCmdAcceptFriend::getId() const {
    return _id;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdAcceptFriend::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_id);
    return {build(writer.build())};
}