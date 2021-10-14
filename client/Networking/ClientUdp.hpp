/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** ClientUdp
*/

#ifndef UDP_HPP_
#define UDP_HPP_

#include <QObject>
#include <QUdpSocket>
#include <Networking/RawPacket.hpp>
#include "LibHandler/LibHandler.hpp"
#include "IClient.hpp"

namespace Babel {
    namespace Networking {
        class ClientUDP : public IClient {
        Q_OBJECT
        public:
            explicit ClientUDP(Management::LibHandler *handler, QObject *parent = nullptr);
            explicit ClientUDP(QObject *parent = nullptr, int inputPort = 80, int outputPort = 8080);
            void send(std::vector<float>);
            void write(Babel::Networking::RawPacket payload) override;
            void startConnection(const std::string &ip, int inputPort, int outputPort) override;
            void stopConnection() override;
            void setInputPort(int port);
            void setOutputPort(int port);
        signals:

        public slots:
            void readyRead() override;

        private:
            std::shared_ptr<Babel::Management::LibHandler> _handler;
            QUdpSocket *_socket;
            int _inputPort;
            int _outputPort;
            QHostAddress _targetIp;
        };
    }
}

#endif /* !UDP_HPP_ */
