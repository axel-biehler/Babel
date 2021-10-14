#include "Call.hpp"

Babel::Networking::Call::Call(int from, int to) : _from(from), _to(to) {
}

int Babel::Networking::Call::getFrom() const {
    return _from;
}

int Babel::Networking::Call::getTo() const {
    return _to;
}

bool Babel::Networking::Call::operator==(const Babel::Networking::Call &other) {
    return _from == other.getFrom() && _to == other.getTo();
}
