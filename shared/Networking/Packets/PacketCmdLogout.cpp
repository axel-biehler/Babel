#include <Networking/Packets/PacketCmdLogout.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketCmdLogout::PacketCmdLogout()
: Packet(PacketType::PacketCmdLogout) {
}

Babel::Networking::Packets::PacketCmdLogout::PacketCmdLogout(std::vector<char> data)
: Packet(PacketType::PacketCmdLogout) {
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdLogout::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    return {build(writer.build())};
}

