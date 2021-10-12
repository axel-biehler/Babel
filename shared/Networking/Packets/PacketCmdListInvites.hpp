#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCmdListInvites : public Packet {
            public:
                PacketCmdListInvites();
                PacketCmdListInvites(std::vector<char> data);

                RawPacket serialize() const;
            };
        }
    }
}