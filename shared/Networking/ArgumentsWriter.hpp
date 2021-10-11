#pragma once

#include <vector>
#include <Networking/Packet.hpp>
#include <string>

namespace Babel {
    namespace Networking {
        class ArgumentsWriter {
        public:
            void addString(const std::string &value);
            void addUnsignedInt(const unsigned int &value);
            void addInt(const int &value);
            void addChar(const char &value);
            void addUnsignedChar(const unsigned char &value);

            std::vector<char> build() const;

        private:
            std::vector<PacketArgType> _types;
            std::vector<char> _data;
        };
    }
}
