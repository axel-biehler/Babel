#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCmdAcceptFriend : public Packet {
            public:
                PacketCmdAcceptFriend(int id);
                PacketCmdAcceptFriend(std::vector<char> data);

                int getId() const;

                RawPacket serialize() const;

            private:
                int _id;
            };
        }
    }
}