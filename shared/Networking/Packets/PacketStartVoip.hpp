#pragma once

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketStartVoip : public Packet {
            public:
                PacketStartVoip(int id, const std::string &ip, int listenPort, int sendPort);
                PacketStartVoip(std::vector<char> data);

                int getId() const;
                std::string getIp() const;
                int getListenPort() const;
                int getSendPort() const;

                RawPacket serialize() const;

            private:
                int _id;
                std::string _ip;
                int _listenPort;
                int _sendPort;
            };
        }
    }
}