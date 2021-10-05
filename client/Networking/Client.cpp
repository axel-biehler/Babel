//
// Created by axel on 22/09/2021.
//

#include "Client.hpp"
#include <iostream>
#include <Networking/Packets/PacketCmdLogin.hpp>
#include <Networking/RawPacket.hpp>

Babel::Networking::Client::Client(std::string adress, u_int16_t port) : QObject(nullptr),
                                                                         _socket(new QTcpSocket(this)),
                                                                         _adress(std::move(adress)),
                                                                         _port(std::move(port))
{
    _in.setDevice(_socket);
    _in.setVersion(QDataStream::Qt_5_15);
    connect(_socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
}

void Babel::Networking::Client::start()
{
    bool running = true;
    std::string str;
    Babel::Networking::Packets::PacketCmdLogin packet("joooooe");
    std::vector<char> rawBytes = packet.serialize().getData();

    for (int i = 0; rawBytes.size() > i; i++)
        str.push_back(rawBytes[i]);

    _socket->connectToHost(QHostAddress(_adress.c_str()), _port);

    if (_socket->waitForConnected()) {
        std::cout << str << std::endl;
        _socket->write(str.c_str(), str.length());
        _socket->flush();
        while (running) {
            std::cin >> str;
            if (str == "exit\n");
                return;
        }
    }
}

void Babel::Networking::Client::read()
{
    QByteArray data = _socket->readAll();
    std::cout << QString(data).data() << std::endl;
}

void Babel::Networking::Client::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}