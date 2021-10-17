#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel::Networking::Packets {
            class PacketCmdListMessages : public Packet {
            public:
                PacketCmdListMessages();
                explicit PacketCmdListMessages(const std::vector<char>& data);

                RawPacket serialize() const;
            };
        }