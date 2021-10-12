#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCmdInviteFriend : public Packet {
            public:
                PacketCmdInviteFriend(const std::string &username);
                PacketCmdInviteFriend(std::vector<char> data);

                std::string getUsername() const;

                RawPacket serialize() const;

            private:
                std::string _username;
            };
        }
    }
}