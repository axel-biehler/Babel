//
// Created by axel on 14/10/2021.
//

#include "PacketCmdListMessages.hpp"
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>

Babel::Networking::Packets::PacketCmdListMessages::PacketCmdListMessages()
        : Packet(PacketType::PacketCmdListMessages) {
}

Babel::Networking::Packets::PacketCmdListMessages::PacketCmdListMessages(std::vector<char> data) : Packet(PacketType::PacketCmdListMessages) {

}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdListMessages::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    return {build(writer.build())};
}
