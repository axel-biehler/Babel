#pragma once

#include <vector>
#include <memory>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        class RawPacket {
        public:
            RawPacket(std::vector<char> data);
            RawPacket(const RawPacket &other);
            RawPacket &operator=(const RawPacket &other);

            std::shared_ptr<Packet> deserialize();
            PacketType getPacketType() const;

            const std::vector<char> getData() const;
            const std::string toStdString() const;

        private:
            std::vector<char> _data;
        };
    }
}