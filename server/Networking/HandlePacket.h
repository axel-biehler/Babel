//
// Created by axel on 11/10/2021.
//

#ifndef BABEL_HANDLEPACKET_H
#define BABEL_HANDLEPACKET_H

#include "Session.hpp"

namespace Babel {
    namespace Networking {
        class HandlePacket {
        public:
            HandlePacket(std::shared_ptr<Babel::Networking::Session> session, std::shared_ptr<Babel::Database::Database> db);

            void handleCmdLoginPacket(RawPacket packet);
        private:
            std::shared_ptr<Babel::Networking::Session> _session;
            std::shared_ptr<Babel::Database::Database> _db;
        };
    }
}


#endif //BABEL_HANDLEPACKET_H
