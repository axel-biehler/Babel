#include <iostream>
#include "ArgumentsReader.hpp"
#include "RawTypes.hpp"

Babel::Networking::ArgumentsReader::ArgumentsReader(const std::vector<char> &data)
    : _data(data), _cursor(sizeof(unsigned int) + 1), _typeCursor(0) {
    char typesCount = _data[_cursor++];

    for (unsigned int i = 0; i < typesCount; i++, _cursor++) {
        _types.push_back(static_cast<PacketArgType>(_data[_cursor]));
    }
}

std::string Babel::Networking::ArgumentsReader::readString() {
    checkType(PacketArgString);
    std::string value;

    for (; _data[_cursor] != '\0'; _cursor++)
        value.push_back(_data[_cursor]);
    _cursor++;
    return value;
}

unsigned int Babel::Networking::ArgumentsReader::readUnsignedInt() {
    checkType(PacketArgUnsignedInt);
    RawUnsignedInt raw{};
    for (int i = 0; i < sizeof(raw.i); i++, _cursor++)
        raw.c[i] = _data[_cursor];
    return raw.i;
}

int Babel::Networking::ArgumentsReader::readInt() {
    checkType(PacketArgInt);
    RawInt raw{};
    for (int i = 0; i < sizeof(raw.i); i++, _cursor++)
        raw.c[i] = _data[_cursor];
    return raw.i;
}

char Babel::Networking::ArgumentsReader::readChar() {
    checkType(PacketArgChar);
    _cursor++;
    return _data[_cursor - 1];
}

std::vector<Babel::Networking::PacketArgType> Babel::Networking::ArgumentsReader::getTypes() const {
    return _types;
}

void Babel::Networking::ArgumentsReader::checkType(Babel::Networking::PacketArgType requiredType) {
    if (_typeCursor >= _types.size())
        std::cerr << "Reading too much in packet!" << std::endl;
    if (_types[_typeCursor] != requiredType)
        std::cerr << "Wrong argument type in packet!" << std::endl;
    _typeCursor++;
}
