#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>
#include <Networking/PacketTypes.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketRespListInvites : public Packet {
            public:
                PacketRespListInvites(std::vector<Invite> friends);
                PacketRespListInvites(std::vector<char> data);

                std::vector<Invite> getInvites() const;

                RawPacket serialize() const;

            private:
                std::vector<Invite> _invites;
            };
        }
    }
}