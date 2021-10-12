//
// Created by axel on 12/10/2021.
//

#ifndef BABEL_IHANDLEPACKET_H
#define BABEL_IHANDLEPACKET_H

#include <Networking/RawPacket.hpp>

namespace Babel {
    namespace Networking {
        class IHandlePacket {
        public:
            virtual RawPacket handleCmdLoginPacket(RawPacket packet) = 0;
            virtual RawPacket handleCmdRegisterPacket(RawPacket rawPacket) = 0;
        };
    }
}

#endif //BABEL_IHANDLEPACKET_H
