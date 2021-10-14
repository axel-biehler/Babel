#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketAcceptCall : public Packet {
            public:
                PacketAcceptCall(int id);
                PacketAcceptCall(std::vector<char> data);

                int getId() const;

                RawPacket serialize() const;

            private:
                int _id;
            };
        }
    }
}