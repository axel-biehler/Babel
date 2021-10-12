#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketRespAcceptFriend : public Packet {
            public:
                PacketRespAcceptFriend(char ok, const std::string &errorMessage, int friendshipId);
                PacketRespAcceptFriend(std::vector<char> data);

                char getOk() const;
                std::string getErrorMessage() const;
                int getFriendshipId() const;

                RawPacket serialize() const;

            private:
                char _ok;
                std::string _errorMessage;
                int _friendshipId;
            };
        }
    }
}