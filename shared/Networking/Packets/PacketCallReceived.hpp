#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCallReceived : public Packet {
            public:
                PacketCallReceived(int id, const std::string &username);
                PacketCallReceived(std::vector<char> data);

                int getId() const;
                std::string getUsername() const;

                RawPacket serialize() const;

            private:
                int _id;
                std::string _username;
            };
        }
    }
}