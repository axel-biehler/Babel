//
// Created by axel on 11/10/2021.
//

#ifndef BABEL_HANDLEPACKET_H
#define BABEL_HANDLEPACKET_H

#include <Networking/RawPacket.hpp>
#include <Database/Database.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include "IHandlepacket.h"
#include "Server.hpp"

namespace Babel {
    namespace Networking {

        class HandlePacket : public IHandlePacket {
        public:
            HandlePacket(std::shared_ptr<Server> server);

            RawPacket handleCmdLoginPacket(RawPacket packet) override;
            RawPacket handleCmdRegisterPacket(RawPacket rawPacket) override;
        private:
            std::shared_ptr<Babel::Networking::Server> _server;
        };
    }
}


#endif //BABEL_HANDLEPACKET_H
