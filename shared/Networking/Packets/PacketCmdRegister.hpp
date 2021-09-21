#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCmdRegister : public Packet {
            public:
                PacketCmdRegister(const std::string &username);
                PacketCmdRegister(std::vector<char> data);

                std::string getUsername() const;

                RawPacket serialize() const;

            private:
                const std::string _username;
            };
        }
    }
}