#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketCmdLogin : public Packet {
            public:
                PacketCmdLogin(const std::string &username, const std::string &password);
                PacketCmdLogin(std::vector<char> data);

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