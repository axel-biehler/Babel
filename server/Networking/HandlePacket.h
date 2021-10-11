//
// Created by axel on 11/10/2021.
//

#ifndef BABEL_HANDLEPACKET_H
#define BABEL_HANDLEPACKET_H

#include <Networking/RawPacket.hpp>
#include <Database/Database.hpp>

namespace Babel {
    namespace Networking {
        class HandlePacket {
        public:
            HandlePacket(std::shared_ptr<Babel::Database::Database> db);

            RawPacket handleCmdLoginPacket(RawPacket packet);
        private:
            std::shared_ptr<Babel::Database::Database> _db;
        };
    }
}


#endif //BABEL_HANDLEPACKET_H
