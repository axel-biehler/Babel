#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketFriendDenied : public Packet {
            public:
                PacketFriendDenied(int id);
                PacketFriendDenied(std::vector<char> data);

                int getId() const;

                RawPacket serialize() const;

            private:
                int _id;
            };
        }
    }
}