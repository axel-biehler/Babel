#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketRespInviteFriend : public Packet {
            public:
                PacketRespInviteFriend(char ok, const std::string &errorMessage);
                PacketRespInviteFriend(std::vector<char> data);

                char getOk() const;
                std::string getErrorMessage() const;

                RawPacket serialize() const;

            private:
                char _ok;
                std::string _errorMessage;
            };
        }
    }
}