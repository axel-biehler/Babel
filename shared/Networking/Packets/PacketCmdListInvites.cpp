#include <Networking/Packets/PacketCmdListInvites.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCmdListInvites::PacketCmdListInvites()
: Packet(PacketType::PacketCmdListInvites) {
}

Babel::Networking::Packets::PacketCmdListInvites::PacketCmdListInvites(std::vector<char> data)
: Packet(PacketType::PacketCmdListInvites) {
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdListInvites::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    return {build(writer.build())};
}

