//
// Created by axel on 14/10/2021.
//

#ifndef BABEL_PACKETMESSAGERECEIVE_HPP
#define BABEL_PACKETMESSAGERECEIVE_HPP

#include <string>
#include <vector>
#include <Networking/RawPacket.hpp>

namespace Babel::Networking::Packets {
    class PacketMessageReceive : public Packet {
    public:
        PacketMessageReceive(int id, const std::string &username);
        explicit PacketMessageReceive(std::vector<char> data);

        int getId() const;
        std::string getUsername() const;

        RawPacket serialize() const;

    private:
        int _id;
        std::string _username;
    };
}

#endif //BABEL_PACKETMESSAGERECEIVE_HPP
