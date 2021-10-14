/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Created by arthur,
*/

#ifndef BABEL_ICLIENT_HPP
#define BABEL_ICLIENT_HPP

#include <QObject>
#include "../../shared/Networking/RawPacket.hpp"

namespace Babel {
    namespace Networking {
        class IClient : public QObject {
        public:
            virtual void write(Babel::Networking::RawPacket payload) = 0;
            virtual void startConnection(const std::string &ip, int inputPort, int outputPort) = 0;
            virtual void stopConnection() = 0;
        public slots:
            virtual void readyRead() = 0;
        };
    }
}

#endif //BABEL_ICLIENT_HPP
