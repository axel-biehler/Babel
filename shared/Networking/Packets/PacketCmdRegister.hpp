#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCmdRegister : public Packet {
            public:
                PacketCmdRegister(const std::string &username, const std::string &password);
                PacketCmdRegister(std::vector<char> data);

                std::string getUsername() const;
                std::string getPassword() const;

                RawPacket serialize() const;

            private:
                std::string _username;
                std::string _password;
            };
        }
    }
}