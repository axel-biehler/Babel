//
// Created by axel on 12/10/2021.
//

#ifndef BABEL_IHANDLEPACKET_HPP
#define BABEL_IHANDLEPACKET_HPP

#include <Networking/RawPacket.hpp>

namespace Babel {
    namespace Networking {

        class Session;

        class IHandlePacket {
        public:
            virtual RawPacket handleCmdLoginPacket(RawPacket packet, Session *session) = 0;
            virtual RawPacket handleCmdRegisterPacket(RawPacket rawPacket, Session *session) = 0;
        };
    }
}

#endif //BABEL_IHANDLEPACKET_HPP
