#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketRespInviteFriend : public Packet {
            public:
                PacketRespInviteFriend(char ok, const std::string &errorMessage, int friendshipId, const std::string &username);
                PacketRespInviteFriend(std::vector<char> data);

                char getOk() const;
                std::string getErrorMessage() const;
                int getFriendshipId() const;
                std::string getUsername() const;

                RawPacket serialize() const;

            private:
                char _ok;
                std::string _errorMessage;
                int _friendshipId;
                std::string _username;
            };
        }
    }
}