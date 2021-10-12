#include <Networking/Packets/PacketCmdDenyFriend.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCmdDenyFriend::PacketCmdDenyFriend(int id)
    : Packet(PacketType::PacketCmdDenyFriend), _id(id) {
}

Babel::Networking::Packets::PacketCmdDenyFriend::PacketCmdDenyFriend(std::vector<char> data)
    : Packet(PacketType::PacketCmdDenyFriend) {
    ArgumentsReader reader{data};
    _id = reader.readInt();
}

int Babel::Networking::Packets::PacketCmdDenyFriend::getId() const {
    return _id;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdDenyFriend::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_id);
    return {build(writer.build())};
}