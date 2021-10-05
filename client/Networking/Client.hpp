//
// Created by axel on 22/09/2021.
//

#ifndef BABEL_CLIENT_HPP
#define BABEL_CLIENT_HPP

#include "QtNetwork"

namespace Babel {
    namespace Networking {
        class Client : public QObject {
        Q_OBJECT
        public:

            Client(std::string adress, u_int16_t port);
            void start();

        private slots:

            void read();
            void bytesWritten(qint64 bytes);


        private:
            QTcpSocket *_socket = nullptr;
            QDataStream _in;
            std::string _adress;
            uint16_t _port;

    };
}
}

#endif //BABEL_CLIENT_HPP
