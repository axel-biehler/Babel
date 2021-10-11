#pragma once

#include <vector>
#include <string>
#include "Packet.hpp"

namespace Babel {
    namespace Networking {
        class ArgumentsReader {
        public:
            ArgumentsReader(const std::vector<char> &data);

            std::string readString();
            unsigned int readUnsignedInt();
            int readInt();
            char readChar();
            unsigned char readUnsignedChar();

            std::vector<PacketArgType> getTypes() const;

        private:
            std::vector<PacketArgType> _types;
            std::vector<char> _data;
            unsigned int _cursor;
            char _typeCursor;

            void checkType(PacketArgType requiredType);
        };
    }
}
