//
// Created by axel on 14/10/2021.
//

#ifndef BABEL_PACKETMESSAGESEND_HPP
#define BABEL_PACKETMESSAGESEND_HPP


#include <Networking/Packet.hpp>
#include <Networking/PacketTypes.hpp>

namespace Babel::Networking::Packets {
    class PacketMessageSend : public Packet {
    public:
        PacketMessageSend();
        PacketMessageSend(Message &message);
        explicit PacketMessageSend(std::vector<char> data);

        Message getMessage() const;
        RawPacket serialize() const;

    private:
        Message _message;
    };
}


#endif //BABEL_PACKETMESSAGESEND_HPP
