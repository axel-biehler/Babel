#include "ArgumentsWriter.hpp"
#include "RawTypes.hpp"

void Babel::Networking::ArgumentsWriter::addString(const std::string &value) {
    _types.push_back(PacketArgString);

    for (char c : value)
        _data.push_back(c);
    _data.push_back(0);
}

void Babel::Networking::ArgumentsWriter::addUnsignedInt(const unsigned int &value) {
    RawUnsignedInt raw{};
    raw.i = value;

    _types.push_back(PacketArgUnsignedInt);

    for (char c : raw.c)
        _data.push_back(c);
}

void Babel::Networking::ArgumentsWriter::addInt(const int &value) {
    RawInt raw{};
    raw.i = value;

    _types.push_back(PacketArgInt);

    for (char c : raw.c)
        _data.push_back(c);
}

void Babel::Networking::ArgumentsWriter::addChar(const char &value) {
    _types.push_back(PacketArgChar);

    _data.push_back(value);
}

std::vector<char> Babel::Networking::ArgumentsWriter::build() const {
    std::vector<char> data;

    data.push_back(static_cast<char>(_types.size()));

    for (auto &type : _types)
        data.push_back(type);
    for (auto c : _data)
        data.push_back(c);
    return data;
}
