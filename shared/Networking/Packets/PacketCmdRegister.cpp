#include <Networking/Packets/PacketCmdRegister.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/RawTypes.hpp>

Babel::Networking::Packets::PacketCmdRegister::PacketCmdRegister(const std::string &username)
    : Packet(PacketType::PacketCmdRegister), _username(username) {
}

Babel::Networking::Packets::PacketCmdRegister::PacketCmdRegister(std::vector<char> data)
    : Packet(PacketType::PacketCmdRegister), _username(data.data() + 7) {
}

std::string Babel::Networking::Packets::PacketCmdRegister::getUsername() const {
    return _username;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketCmdRegister::serialize() const {

    Babel::Networking::RawInt rawLen{};
    std::vector<char> data{0, 0, 0, 0, static_cast<char>(_packetType), 1, PacketArgString};

    for (char c : _username)
        data.push_back(c);
    data.push_back(0);
    rawLen.i = data.size();
    for (int i = 0; i < sizeof(rawLen.c); i++)
        data[i] = rawLen.c[i];
    return {data};
}

