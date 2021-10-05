//
// Created by axel on 22/09/2021.
//

#include "Client.hpp"
#include <iostream>
#include <Networking/Packets/PacketCmdLogin.hpp>
#include <Networking/RawPacket.hpp>
#include <Networking/RawTypes.hpp>

Babel::Networking::Client::Client(std::string adress, u_int16_t port) : QObject(nullptr),
                                                                         _socket(new QTcpSocket(this)),
                                                                         _adress(std::move(adress)),
                                                                         _port(std::move(port))
{
    _in.setDevice(_socket);
    _in.setVersion(QDataStream::Qt_5_15);
    connect(_socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Babel::Networking::Client::start()
{
    std::string str;
    Babel::Networking::Packets::PacketCmdLogin packet("joooooe");
    std::vector<char> rawBytes = packet.serialize().getData();

    for (int i = 0; rawBytes.size() > i; i++)
        str.push_back(rawBytes[i]);

    _socket->connectToHost(QHostAddress(_adress.c_str()), _port);

    if (_socket->waitForConnected()) {
        _socket->write(str.c_str(), str.length());
        _socket->flush();
    }
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
    handle_packet(rawPacket);
}

void Babel::Networking::Client::write(Babel::Networking::RawPacket rawPacket)
{
    _socket->write(rawPacket.toStdString().c_str());
}

void Babel::Networking::Client::handle_packet(Babel::Networking::RawPacket rawPacket)
{
    switch (rawPacket.getPacketType()) {
        case Babel::Networking::PacketType::PacketCmdLogin:
            auto newPacket = std::static_pointer_cast<Babel::Networking::Packets::PacketCmdLogin>(
                    rawPacket.deserialize());
            std::cout << newPacket->getUsername() << std::endl;
            break;
    }
}

void Babel::Networking::Client::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}