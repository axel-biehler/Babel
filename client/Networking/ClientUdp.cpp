/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** ClientUdp
*/

#include <iostream>
#include <utility>
#include "ClientUdp.hpp"

Babel::Networking::ClientUDP::ClientUDP(Management::LibHandler *handler, QObject *parent) :
    IClient(), _handler(std::move(handler))
{
    _socket = new QUdpSocket(this);

    _socket->bind(QHostAddress::LocalHost, 1234);
    _inputPort = 1234;
    _outputPort = 1234;
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

Babel::Networking::ClientUDP::ClientUDP(std::shared_ptr<Babel::Management::LibHandler> handler, QObject *parent, int inputPort, int outputPort) :
    IClient(), _handler(std::move(handler)), _inputPort(inputPort), _outputPort(outputPort)
{
    _socket = new QUdpSocket(this);

    _socket->bind(QHostAddress::LocalHost, _inputPort);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Babel::Networking::ClientUDP::write(Babel::Networking::RawPacket payload) {
    QByteArray Data(payload.toStdString().c_str());

    _socket->writeDatagram(Data, QHostAddress::LocalHost, _outputPort);
}

void Babel::Networking::ClientUDP::readyRead()
{
    QByteArray buffer;
    buffer.resize(_socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    _socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    std::string str = buffer.toStdString();
    RawPacket received(std::vector<char>(str.begin(), str.end()));

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
}

void Babel::Networking::ClientUDP::setInputPort(int port) {
    _inputPort = port;
}

void Babel::Networking::ClientUDP::setOutputPort(int port) {
    _outputPort = port;
}
