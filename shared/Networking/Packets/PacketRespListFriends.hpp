#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>
#include <Networking/PacketTypes.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketRespListFriends : public Packet {
            public:
                PacketRespListFriends(std::vector<User> friends);
                PacketRespListFriends(std::vector<char> data);

                std::vector<User> getFriends() const;

                RawPacket serialize() const;

            private:
                std::vector<User> _friends;
            };
        }
    }
}