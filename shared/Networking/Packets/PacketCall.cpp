#include <Networking/Packets/PacketCall.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCall::PacketCall(int id)
    : Packet(PacketType::PacketCall), _id(id) {
}

Babel::Networking::Packets::PacketCall::PacketCall(std::vector<char> data)
    : Packet(PacketType::PacketCall) {
    ArgumentsReader reader{data};
    _id = reader.readInt();
}

int Babel::Networking::Packets::PacketCall::getId() const {
    return _id;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCall::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_id);
    return {build(writer.build())};
}