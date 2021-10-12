#include <Networking/Packets/PacketCmdListFriends.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCmdListFriends::PacketCmdListFriends()
: Packet(PacketType::PacketCmdListFriends) {
}

Babel::Networking::Packets::PacketCmdListFriends::PacketCmdListFriends(std::vector<char> data)
: Packet(PacketType::PacketCmdListFriends) {
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdListFriends::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    return {build(writer.build())};
}

