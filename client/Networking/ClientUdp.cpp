/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** ClientUdp
*/

#include <iostream>
#include <utility>
#include <Networking/RawTypes.hpp>
#include "ClientUdp.hpp"
#include "Networking/Packets/PacketAudio.hpp"
#include "Networking/Packets/PacketCmdLogin.hpp"
#include "Networking/Packet.hpp"

Babel::Networking::ClientUDP::ClientUDP(Management::LibHandler *handler, QObject *parent) :
    IClient(), _handler(std::move(handler))
{
}

Babel::Networking::ClientUDP::ClientUDP(QObject *parent, int inputPort, int outputPort) :
    IClient(), _inputPort(inputPort), _outputPort(outputPort)
{
    _handler = std::make_shared<Babel::Management::LibHandler>();
}

void Babel::Networking::ClientUDP::write(std::vector<unsigned char> payload) {
    //QByteArray Data(payload.data(), payload.size());

    _socket->writeDatagram((char *)&payload[0], payload.size(), QHostAddress::LocalHost, _outputPort);
}

void Babel::Networking::ClientUDP::startConnection(const std::string &ip, int inputPort, int outputPort) {
    _handler->get_lib_audio()->set_sender(this);
    _socket = new QUdpSocket(this);

    _inputPort = inputPort;
    _outputPort = outputPort;
    _targetIp.setAddress(ip.c_str());
    _socket->bind(_targetIp, _inputPort);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    _handler->start();
}

void Babel::Networking::ClientUDP::readyRead()
{
    std::vector<unsigned char> buffer;
    buffer.resize(_socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    _socket->readDatagram((char *)&buffer[0], buffer.size(), &sender, &senderPort);
    auto decoded_sample = _handler->get_lib_compressor()->decode(buffer);
    _handler->get_lib_audio()->add_sample(decoded_sample);
}

void Babel::Networking::ClientUDP::setInputPort(int port) {
    _inputPort = port;
}

void Babel::Networking::ClientUDP::setOutputPort(int port) {
    _outputPort = port;
}

void Babel::Networking::ClientUDP::stopConnection() {
    _handler->stop();
    delete _socket;
}

void Babel::Networking::ClientUDP::send(std::vector<float> sample) {
    auto encoder = _handler->get_lib_compressor();
    auto compressed = encoder->encode(std::move(sample));
    write(compressed);
}
