//
// Created by alexandre on 12/10/2021.
//

#ifndef BABEL_PACKETTYPES_HPP
#define BABEL_PACKETTYPES_HPP

#include <string>

namespace Babel {
    namespace Networking {
        struct User {
            int id;
            std::string username;
        };

        struct Invite {
            int id;
            std::string fromUsername;
            std::string toUsername;
            int from;
            int to;
        };

        struct Message {
            int id;
            std::string body;
            std::string fromUsername;
            std::string toUsername;
            int from;
            int to;
            unsigned long timestamp;
            int status;
        };
    }
}

#endif //BABEL_PACKETTYPES_HPP
