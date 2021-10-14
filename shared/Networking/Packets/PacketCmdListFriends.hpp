#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCmdListFriends : public Packet {
            public:
                PacketCmdListFriends();
                PacketCmdListFriends(std::vector<char> data);

                RawPacket serialize() const;
            };
        }
    }
}