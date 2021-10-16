//
// Created by axel on 14/10/2021.
//

#include "PacketRespListMessages.hpp"
#include <Networking/ArgumentsWriter.hpp>
#include <Networking/ArgumentsReader.hpp>
#include <algorithm>

Babel::Networking::Packets::PacketRespListMessages::PacketRespListMessages(std::vector<Message> messages) : Packet(PacketType::PacketRespListMessages), _messages(messages) {

}

Babel::Networking::Packets::PacketRespListMessages::PacketRespListMessages(std::vector<char> data) : Packet(PacketType::PacketRespListMessages) {
    ArgumentsReader reader{data};
    auto count = reader.readInt();

    for (int i = 0; i < count; i++) {
        Message message;
        message.id = reader.readInt();
        message.body = reader.readString();
        message.fromUsername = reader.readString();
        message.toUsername = reader.readString();
        message.from = reader.readInt();
        message.to = reader.readInt();
        message.timestamp = reader.readInt();
        _messages.push_back(message);

        std::sort(_messages.begin(), _messages.end(), [](Babel::Networking::Message &lhs, Babel::Networking::Message &rhs) {
            return lhs.timestamp < rhs.timestamp;
        });
    }
}

std::vector<Babel::Networking::Message> Babel::Networking::Packets::PacketRespListMessages::getMessages() const {
    return _messages;
}

Babel::Networking::RawPacket Babel::Networking::Packets::PacketRespListMessages::serialize() const {
    Babel::Networking::ArgumentsWriter writer;

    writer.addInt(_messages.size());
    for (auto &mess : _messages) {
        writer.addInt(mess.id);
        writer.addString(mess.body);
        writer.addString(mess.fromUsername);
        writer.addString(mess.toUsername);
        writer.addInt(mess.from);
        writer.addInt(mess.to);
        writer.addInt(mess.timestamp);
    }
    return {build(writer.build())};
}


