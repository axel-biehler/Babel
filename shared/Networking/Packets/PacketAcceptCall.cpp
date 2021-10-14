#include <Networking/Packets/PacketAcceptCall.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketAcceptCall::PacketAcceptCall(int id)
    : Packet(PacketType::PacketAcceptCall), _id(id) {
}

Babel::Networking::Packets::PacketAcceptCall::PacketAcceptCall(std::vector<char> data)
    : Packet(PacketType::PacketAcceptCall) {
    ArgumentsReader reader{data};
    _id = reader.readInt();
}

int Babel::Networking::Packets::PacketAcceptCall::getId() const {
    return _id;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketAcceptCall::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_id);
    return {build(writer.build())};
}