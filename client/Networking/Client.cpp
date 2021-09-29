//
// Created by axel on 22/09/2021.
//

#include "Client.hpp"
#include <iostream>

Babel::Networking::Client::Client(std::string adress, u_int16_t port) : QObject(nullptr),
                                                                         _socket(new QTcpSocket(this)),
                                                                         _adress(std::move(adress)),
                                                                         _port(std::move(port))
{
    _in.setDevice(_socket);
    _in.setVersion(QDataStream::Qt_5_15);
}

void Babel::Networking::Client::start()
{
    bool running = true;
    connect(_socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    _socket->connectToHost(QHostAddress(_adress.c_str()), _port);

    if (_socket->waitForConnected()) {
        while (running) {
            std::cout << "here" << std::endl;
            std::string input;

            std::cin >> input;
            _socket->write("azer");
            if (input == "exit\n")
                running == false;
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