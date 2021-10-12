//
// Created by axel on 11/10/2021.
//

#ifndef BABEL_HANDLEPACKET_HPP
#define BABEL_HANDLEPACKET_HPP

#include <Networking/RawPacket.hpp>
#include "IHandlePacket.hpp"
#include "Server.hpp"

namespace Babel {
    namespace Networking {

        class Session;

        class HandlePacket : public IHandlePacket {
        public:
            HandlePacket(std::shared_ptr<Server> server);

            RawPacket handleCmdLoginPacket(RawPacket packet, Session *session) override;
            RawPacket handleCmdRegisterPacket(RawPacket rawPacket, Session *session) override;
            RawPacket handleCmdInviteFriendPacket(RawPacket rawPacket, Session *session) override;
            RawPacket handleCmdListInvites(RawPacket rawPacket, Session *session) override;
        private:
            std::shared_ptr<Babel::Networking::Server> _server;
        };
    }
}


#endif //BABEL_HANDLEPACKET_HPP
