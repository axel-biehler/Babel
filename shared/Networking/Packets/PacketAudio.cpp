/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#include "Networking/Packets/PacketAudio.hpp"
#include "Networking/RawPacket.hpp"
#include "Networking/ArgumentsWriter.hpp"
#include "Networking/ArgumentsReader.hpp"

Babel::Networking::Packets::PacketAudio::PacketAudio(const std::vector<unsigned char> &sample)
    : Packet(PacketType::PacketAudio), _sample(sample) {
}

Babel::Networking::Packets::PacketAudio::PacketAudio(std::vector<char> data)
    : Packet(PacketType::PacketAudio) {
    ArgumentsReader reader{data};
    int size = reader.readInt();

    for (int i = 0; i < size; ++i) {
        _sample.push_back(reader.readUnsignedChar());
    }
}

std::vector<unsigned char> Babel::Networking::Packets::PacketAudio::getSample() const {
    return _sample;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketAudio::serialize() const {
    Babel::Networking::ArgumentsWriter writer;

    writer.addInt(static_cast<int>(_sample.size()));
    for (unsigned char c : _sample)
        writer.addUnsignedChar(c);
    return {build(writer.build())};
}
