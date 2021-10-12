//
// Created by axel on 22/09/2021.
//

#ifndef BABEL_CLIENT_HPP
#define BABEL_CLIENT_HPP

#include <Networking/RawPacket.hpp>
#include "QtNetwork"

namespace Babel {
    namespace Networking {
        class   Client : public QObject {
        Q_OBJECT
        public:
            Client();
            void start(const QString &address, quint16 port);
            void write(Babel::Networking::RawPacket rawPacket);
            bool isConnected() const;

        signals:
            void packetReceive(Babel::Networking::RawPacket);

        private slots:
            void readyRead();

        private:
            QTcpSocket *_socket = nullptr;
            QDataStream _in;
        };
    }
}

#endif //BABEL_CLIENT_HPP
