#include <Networking/Packets/PacketRespListInvites.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <iostream>

Babel::Networking::Packets::PacketRespListInvites::PacketRespListInvites(std::vector<Invite> invites)
    : Packet(PacketType::PacketRespListInvites), _invites(invites) {
}

Babel::Networking::Packets::PacketRespListInvites::PacketRespListInvites(std::vector<char> data)
    : Packet(PacketType::PacketRespListInvites) {
    ArgumentsReader reader{data};
    auto count = reader.readInt();
    for (int i = 0; i < count; i++) {
        Invite inv;
        inv.id = reader.readInt();
        inv.username = reader.readString();
        _invites.push_back(inv);
    }
}

std::vector<Babel::Networking::Invite> Babel::Networking::Packets::PacketRespListInvites::getInvites() const {
    return _invites;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespListInvites::serialize() const {
    Babel::Networking::ArgumentsWriter writer;
    writer.addInt(_invites.size());
    for (auto &inv : _invites) {
        writer.addInt(inv.id);
        writer.addString(inv.username);
    }
    return {build(writer.build())};
}