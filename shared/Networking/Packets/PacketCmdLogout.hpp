#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCmdLogout : public Packet {
            public:
                PacketCmdLogout();
                PacketCmdLogout(std::vector<char> data);

                RawPacket serialize() const;
            };
        }
    }
}