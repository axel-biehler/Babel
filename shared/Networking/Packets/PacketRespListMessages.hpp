//
// Created by axel on 14/10/2021.
//

#ifndef BABEL_PACKETRESPLISTMESSAGES_HPP
#define BABEL_PACKETRESPLISTMESSAGES_HPP

#include <vector>
#include <Networking/RawPacket.hpp>
#include <Networking/PacketTypes.hpp>

namespace Babel::Networking::Packets {
    class PacketRespListMessages : public Packet {
        public:
            explicit PacketRespListMessages(std::vector<Message> messages);
            explicit PacketRespListMessages(std::vector<char> data);

            std::vector<Message> getMessages() const;

            RawPacket serialize() const;

        private:
            std::vector<Message> _messages;
    };
}


#endif //BABEL_PACKETRESPLISTMESSAGES_HPP
