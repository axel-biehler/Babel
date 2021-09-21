/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Session
*/

#include "Session.hpp"

Babel::Networking::Session::Session(asio::ip::tcp::socket &&socket) : _socket(std::move(socket))
{
}

Babel::Networking::Session::~Session()
{
}

void Babel::Networking::Session::start()
{
    read();
}

void Babel::Networking::Session::read()
{
    asio::async_read_until(_socket, _streambuf, '\n', [self = shared_from_this()] (std::error_code err, std::size_t bytes_transferred)
    {
        std::cout << std::istream(&self->_streambuf).rdbuf();
        self->write();
    });
}

void  Babel::Networking::Session::write()
{
    asio::write(_socket, _streambuf);
}