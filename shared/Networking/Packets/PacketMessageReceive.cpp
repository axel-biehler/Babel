//
// Created by axel on 14/10/2021.
//

#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include "PacketMessageReceive.hpp"

Babel::Networking::Packets::PacketMessageReceive::PacketMessageReceive(int id, const std::string &username) :
    Packet(PacketType::PacketMessageReceive), _id(id), _username(username){

}

Babel::Networking::Packets::PacketMessageReceive::PacketMessageReceive(std::vector<char> data) : Packet(PacketType::PacketMessageReceive) {
    ArgumentsReader reader{data};

    _id = reader.readInt();
    _username = reader.readString();
}

int Babel::Networking::Packets::PacketMessageReceive::getId() const {
    return _id;
}

std::string Babel::Networking::Packets::PacketMessageReceive::getUsername() const {
    return _username;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketMessageReceive::serialize() const {
    ArgumentsWriter writer;

    writer.addInt(_id);
    writer.addString(_username);
    return {build(writer.build())};
}
