#pragma once

#include <vector>

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
            PacketAudio,
            PacketCmdInviteFriend,
            PacketRespInviteFriend,
            PacketCmdAcceptFriend,
            PacketRespAcceptFriend,
            PacketCmdDenyFriend,
            PacketRespDenyFriend,
            PacketInviteReceived,
            PacketFriendAdded,
            PacketFriendDenied,
            PacketCmdListFriends,
            PacketRespListFriends,
            PacketCmdListInvites,
            PacketRespListInvites,
            PacketCall,
            PacketCallReceived,
            PacketAcceptCall,
            PacketStartVoip,
        };

        enum PacketArgType {
            PacketArgString,
            PacketArgUnsignedInt,
            PacketArgInt,
            PacketArgChar,
            PacketArgUnsignedChar,
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
            std::vector<char> build(std::vector<char> content) const;
        };
    }
}

