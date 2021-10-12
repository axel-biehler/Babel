//
// Created by axel on 22/09/2021.
//

#include "Client.hpp"
#include <iostream>
#include <Networking/Packets/PacketCmdLogin.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/RawTypes.hpp>

Babel::Networking::Client::Client() : QObject(nullptr), _socket(new QTcpSocket(this))
{
    _in.setDevice(_socket);
    _in.setVersion(QDataStream::Qt_5_15);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Babel::Networking::Client::start(const QString &address, quint16 port)
{
    _socket->connectToHost(QHostAddress(address), port);
    _socket->waitForConnected();
}

void Babel::Networking::Client::readyRead()
{
    QByteArray datas = _socket->readAll();
    std::string str = datas.toStdString();
    RawInt raw{};
    std::vector<char> bytesArray;

    for (int i = 0; i < sizeof(raw.i); i++)
        raw.c[i] = str[i];
    for (int i = 0; i < raw.i; i++)
        bytesArray.push_back(str[i]);
    auto rawPacket = Babel::Networking::RawPacket(bytesArray);
    emit packetReceive(rawPacket);
}

void Babel::Networking::Client::write(Babel::Networking::RawPacket rawPacket)
{
    _socket->write(rawPacket.getData().data(), rawPacket.getData().size());
    _socket->flush();
}

bool Babel::Networking::Client::isConnected() const {
    return _socket->state() == QAbstractSocket::ConnectedState;
}
