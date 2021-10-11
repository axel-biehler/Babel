#pragma once

namespace Babel {
    namespace Networking {
        union RawInt {
            char c[4];
            int i;
        };
        union RawUnsignedInt {
            char c[4];
            unsigned int i;
        };
        union RawUnsignedChar {
            char c;
            unsigned char u;
        };
    }
}