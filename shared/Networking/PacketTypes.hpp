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
            std::string username;
        };
    }
}

#endif //BABEL_PACKETTYPES_HPP
