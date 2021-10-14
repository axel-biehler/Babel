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
    _socket = new QUdpSocket(this);

    /*_socket->bind(QHostAddress::LocalHost, 1234);
    _inputPort = 1234;
    _outputPort = 1234;*/
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

Babel::Networking::ClientUDP::ClientUDP(QObject *parent, int inputPort, int outputPort) :
    IClient(), _inputPort(inputPort), _outputPort(outputPort)
{
    _handler = std::make_shared<Babel::Management::LibHandler>();
    _socket = new QUdpSocket(this);

    _inputPort = inputPort;
    _outputPort = outputPort;
    _targetIp.setAddress("127.0.0.1");
    _socket->bind(_targetIp, _inputPort);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    //TODO : end remove here
}

void Babel::Networking::ClientUDP::write(Babel::Networking::RawPacket payload) {
    auto charVector = payload.getData();
    std::string payload_str(charVector.begin(), charVector.end());
    QByteArray Data(payload_str.data());

    _socket->writeDatagram(Data, QHostAddress::LocalHost, _outputPort);
    //_socket->writeDatagram(packet_audio.serialize().getData().data(), QHostAddress::LocalHost, _outputPort);
    //_socket->writeDatagram(payload.getData().data(), QHostAddress::LocalHost, _outputPort);
}

void Babel::Networking::ClientUDP::startConnection(const std::string &ip, int inputPort, int outputPort) {
    _handler->get_lib_audio()->set_sender(this);
    //_socket = new QUdpSocket(this);

    _inputPort = inputPort;
    _outputPort = outputPort;
    _targetIp.setAddress(ip.c_str());
    //_socket->bind(_targetIp, _inputPort);
    //connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    _handler->start();
}

void Babel::Networking::ClientUDP::readyRead()
{
    QByteArray buffer;
    buffer.resize(_socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    std::cout << "je recois un paquet" << std::endl;
    _socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    RawPacket received(std::vector<char>(buffer.begin(), buffer.end()));
    if (received.getPacketType() != Babel::Networking::PacketAudio)
        return;

    std::cout << "je recois un paquet audio !" << std::endl;

    Babel::Networking::Packets::PacketAudio packetAudio(received.getData());
    auto decoded_sample = _handler->get_lib_compressor()->decode(packetAudio.getSample());
    _handler->get_lib_audio()->add_sample(decoded_sample);
}

void Babel::Networking::ClientUDP::setInputPort(int port) {
    _inputPort = port;
}

void Babel::Networking::ClientUDP::setOutputPort(int port) {
    _outputPort = port;
}

void Babel::Networking::ClientUDP::stopConnection() {
    delete _socket;
}

void Babel::Networking::ClientUDP::send(std::vector<float> sample) {
    auto encoder = _handler->get_lib_compressor();
    Babel::Networking::Packets::PacketAudio encodedPacket(encoder->encode(std::move(sample)));

    write(encodedPacket.serialize());
}
