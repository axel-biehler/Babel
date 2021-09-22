/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Session
*/

#include "Session.hpp"

Babel::Networking::Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket) : _socket(socket)
{
}

Babel::Networking::Session::Session(const Session &session) : _socket(session.getSocket()), _streambuf(session.getStreambuf())
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
    asio::async_read_until(*_socket, *_streambuf, '\n', [self = shared_from_this()] (std::error_code err, std::size_t bytes_transferred)
    {
        std::cout << std::istream(self->_streambuf.get()).rdbuf();
        self->write();
        self->read();
    });
}

void  Babel::Networking::Session::write()
{
    asio::write(*_socket, *_streambuf);
}

//setter getter
void Babel::Networking::Session::setSocket(const std::shared_ptr<asio::ip::tcp::socket> socket)
{
    _socket = socket;
}

std::shared_ptr<asio::ip::tcp::socket> Babel::Networking::Session::getSocket() const
{
    return _socket;
}

void Babel::Networking::Session::setStreambuf(const std::shared_ptr<asio::streambuf> streambuffer)
{
    _streambuf = streambuffer;
}

std::shared_ptr<asio::streambuf> Babel::Networking::Session::getStreambuf() const
{
    return _streambuf;
}