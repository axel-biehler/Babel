/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Session
*/

#include "Session.hpp"
#include <Networking/RawPacket.hpp>

Babel::Networking::Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket) : _socket(socket)
{
    _data = (char *)(malloc(1024));
}

Babel::Networking::Session::Session(const Session &session) : _socket(session.getSocket())
{
    _data = (char *)(malloc(1024));
}

Babel::Networking::Session::~Session()
{
    free(_data);
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
            unsigned int size = std::stoi(_data, 0, 2);
            _socket->read_some(asio::buffer(_data, size));
            for (int i = 0; _data[i]; i++)
                _buffer.push_back(_data[i]);
            auto rawPacket = Babel::Networking::RawPacket(_buffer);
        }
        catch (std::invalid_argument err) {
            std::cerr << err.what() << std::endl;
        }

    }
}

void Babel::Networking::Session::handle_packet(Babel::Networking::RawPacket rawPacket)
{
    switch (rawPacket.getPacketType()) {
        default:
            return;
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