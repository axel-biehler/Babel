//
// Created by axel on 14/10/2021.
//

#include <Networking/ArgumentsReader.hpp>
#include <Networking/ArgumentsWriter.hpp>
#include "PacketMessageSend.hpp"

Babel::Networking::Packets::PacketMessageSend::PacketMessageSend(Babel::Networking::Message &message) : Packet(PacketType::PacketMessageSend),
                                                                                                       _message(message) {

}

Babel::Networking::Packets::PacketMessageSend::PacketMessageSend(std::vector<char> data) : Packet(PacketType::PacketMessageSend) {
    ArgumentsReader reader{data};

    _message.id = reader.readInt();
    _message.to = reader.readInt();
    _message.from = reader.readInt();
    _message.status = reader.readInt();
    _message.timestamp = reader.readInt();
    _message.body = reader.readString();
}

Babel::Networking::Message Babel::Networking::Packets::PacketMessageSend::getMessage() const {
    return _message;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketMessageSend::serialize() const {
    Babel::Networking::ArgumentsWriter writer;

    writer.addInt(_message.id);
    writer.addInt(_message.to);
    writer.addInt(_message.from);
    writer.addInt(_message.status);
    writer.addInt(_message.timestamp);
    writer.addString(_message.body);
    return {build(writer.build())};
}