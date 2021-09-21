#pragma once

namespace Babel {
    namespace Networking {
        class RawPacket;

        enum PacketType {
            PacketUnknown,
            PacketCmdRegister,
            PacketRespRegister,
            PacketCmdLogin,
            PacketRespLogin,
            PacketCmdLogout,
            PacketCmdListOnlineUsers,
            PacketRespListOnlineUsers,
        };

        enum PacketArgType {
            PacketArgString,
            PacketArgUnsignedInt,
            PacketArgInt,
            PacketArgChar,
        };

        class Packet {
        public:
            Packet(PacketType packetType);
            Packet(const RawPacket &raw);
            Packet(const Packet &other) = default;
            Packet &operator=(const Packet &other) = delete;

            RawPacket serialize();

            PacketType getPacketType() const;

        protected:
            PacketType _packetType;
        };
    }
}

