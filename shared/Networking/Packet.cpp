#include <Networking/Packet.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Packet::Packet(Babel::Networking::PacketType packetType) : _packetType(packetType) {
}

Babel::Networking::RawPacket Babel::Networking::Packet::serialize() {
    return {std::vector<char>({})};
}

Babel::Networking::PacketType Babel::Networking::Packet::getPacketType() const {
    return _packetType;
}