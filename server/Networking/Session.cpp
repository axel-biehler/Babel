/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Session
*/

#include "Session.hpp"
#include <Networking/RawPacket.hpp>
#include <Networking/RawTypes.hpp>
#include <Networking/Packets/PacketCmdLogin.hpp>

Babel::Networking::Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket) : _socket(socket)
{
    _data = (char *)(malloc(1024));
    _size_str = (char *)(malloc(4));
}

Babel::Networking::Session::Session(const Session &session) : _socket(session.getSocket())
{
    _data = (char *)(malloc(1024));
}

Babel::Networking::Session::~Session()
{
    free(_data);
    free(_size_str);
}

void Babel::Networking::Session::start()
{
    read();
}


void Babel::Networking::Session::read()
{
    // Schedule asynchronous receiving of a data
    _socket->async_receive( asio::buffer(_data, 4), std::bind(&Session::on_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void Babel::Networking::Session::on_read(std::error_code error, std::size_t bytes_transferred)
{
    if(!error)
    {
        try {
            RawInt raw{};
            for (int i = 0; i < sizeof(raw.i); i++)
                raw.c[i] = _data[i];
            for (int i = 0; i < 4; i++)
                _buffer.push_back(_data[i]);
            _size = raw.i - 4;
            _socket->async_receive(asio::buffer(_data, raw.i - 4), std::bind(&Session::on_read_data, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
        }
        catch (std::invalid_argument err) {
            std::cerr << err.what() << std::endl;
        }
    }
}

void Babel::Networking::Session::on_read_data(std::error_code error, std::size_t bytes_transferred)
{
    if (!error) {
        for (int i = 0; i < _size; i++)
            _buffer.push_back(_data[i]);
        auto rawPacket = Babel::Networking::RawPacket(_buffer);
        handle_packet(rawPacket);
    }
}

void Babel::Networking::Session::handle_packet(Babel::Networking::RawPacket rawPacket) {
    switch (rawPacket.getPacketType()) {
        case Babel::Networking::PacketType::PacketCmdLogin:
            auto newPacket = std::static_pointer_cast<Babel::Networking::Packets::PacketCmdLogin>(
                    rawPacket.deserialize());
            std::cout << newPacket->getUsername() << std::endl;
            break;

    }
}

void Babel::Networking::Session::write()
{
    // Schedule asynchronous sending of the data
    _socket->async_send(asio::buffer(_data, 4), std::bind(&Session::on_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void Babel::Networking::Session::on_write(std::error_code error, std::size_t bytes_transferred) {
    if (!error) {
        // When the data is sent and no error occurred, return to the first step
        read();
    }
}

//setter getter

std::shared_ptr<asio::ip::tcp::socket> Babel::Networking::Session::getSocket() const
{
    return _socket;
}

char *Babel::Networking::Session::getDate() const {
    return _data;
}