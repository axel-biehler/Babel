#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketRespRegister : public Packet {
            public:
                PacketRespRegister(char ok, const std::string &errorMessage);
                PacketRespRegister(std::vector<char> data);

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