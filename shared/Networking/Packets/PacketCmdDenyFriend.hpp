#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCmdDenyFriend : public Packet {
            public:
                PacketCmdDenyFriend(int id);
                PacketCmdDenyFriend(std::vector<char> data);

                int getId() const;

                RawPacket serialize() const;

            private:
                int _id;
            };
        }
    }
}