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

            Client(std::string adress, u_int16_t port);
            void start();

        signals:
            /*
             * when packet receive emit signal you need to connect your slot function to connect
             * your object with this object => connect(Object1(this), PacketReceive, Object2, yourSlotFunc);
             * https://doc.qt.io/qt-5/signalsandslots.html
             */
            void packetReceive(Babel::Networking::RawPacket);

        private slots:

            void readyRead();
            void write(Babel::Networking::RawPacket rawPacket);
            void bytesWritten(qint64 bytes);

        private:
            QTcpSocket *_socket = nullptr;
            QDataStream _in;
            std::string _adress;
            uint16_t _port;
            void handle_packet(Babel::Networking::RawPacket rawPacket);
        };
    }
}

#endif //BABEL_CLIENT_HPP
