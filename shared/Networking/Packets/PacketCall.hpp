#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCall : public Packet {
            public:
                PacketCall(int id);
                PacketCall(std::vector<char> data);

                int getId() const;

                RawPacket serialize() const;

            private:
                int _id;
            };
        }
    }
}