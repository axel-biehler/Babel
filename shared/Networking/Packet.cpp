#include <Networking/Packet.hpp>
#include <Networking/RawPacket.hpp>
#include "RawTypes.hpp"

Babel::Networking::Packet::Packet(Babel::Networking::PacketType packetType) : _packetType(packetType) {
}

Babel::Networking::RawPacket Babel::Networking::Packet::serialize() {
    return {std::vector<char>({})};
}

Babel::Networking::PacketType Babel::Networking::Packet::getPacketType() const {
    return _packetType;
}

std::vector<char> Babel::Networking::Packet::build(std::vector<char> content) const {
    Babel::Networking::RawUnsignedInt rawLen{};
    std::vector<char> data{0, 0, 0, 0, static_cast<char>(_packetType)};

    for (auto c : content)
        data.push_back(c);

    rawLen.i = data.size();
    for (int i = 0; i < sizeof(rawLen.c); i++)
        data[i] = rawLen.c[i];
    return data;
}
