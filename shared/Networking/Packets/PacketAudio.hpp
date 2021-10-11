/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#ifndef BABEL_PACKETAUDIO_HPP
#define BABEL_PACKETAUDIO_HPP

#include <vector>
#include <string>
#include <Networking/Packet.hpp>

namespace Babel {
    namespace Networking {
        namespace Packets {
            class PacketAudio : public Packet {
            public:
                PacketAudio(const std::vector<unsigned char> &sample);
                PacketAudio(std::vector<char> data);

                std::vector<unsigned char> getSample() const;

                RawPacket serialize() const;

            private:
                std::vector<unsigned char> _sample;
            };
        }
    }
}

#endif //BABEL_PACKETAUDIO_HPP
