#include <Networking/Packets/PacketStartVoip.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketStartVoip::PacketStartVoip(int id, const std::string &ip, int listenPort, int sendPort)
    : Packet(PacketType::PacketStartVoip), _id(id), _ip(ip), _listenPort(listenPort), _sendPort(sendPort) {
}

Babel::Networking::Packets::PacketStartVoip::PacketStartVoip(std::vector<char> data)
    : Packet(PacketType::PacketStartVoip) {
    ArgumentsReader reader{data};
    _id = reader.readInt();
    _ip = reader.readString();
    _listenPort = reader.readInt();
    _sendPort = reader.readInt();
}

int Babel::Networking::Packets::PacketStartVoip::getId() const {
    return _id;
}

std::string Babel::Networking::Packets::PacketStartVoip::getIp() const {
    return _ip;
}

int Babel::Networking::Packets::PacketStartVoip::getListenPort() const {
    return _listenPort;
}

int Babel::Networking::Packets::PacketStartVoip::getSendPort() const {
    return _sendPort;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketStartVoip::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_id);
    writer.addString(_ip);
    writer.addInt(_listenPort);
    writer.addInt(_sendPort);
    return {build(writer.build())};
}