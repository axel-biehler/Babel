/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Session
*/

#include "Session.hpp"

Babel::Networking::Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket) : _socket(socket)
{
    memset(_data, 0, 1024);
}

Babel::Networking::Session::Session(const Session &session) : _socket(session.getSocket())
{
    memset(_data, 0, 1024);
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
    _socket->async_read_some(asio::buffer(_data, 4), [this] (std::error_code err, std::size_t bytes_transferred) {
        std::cout << "nice cock bro" << std::endl;
          if (!err) {
              std::string str(_data, bytes_transferred);
              _buffer.insert(_buffer.end(), str.begin(), str.end());
              std::cout << str << std::endl;
              //read();
        } else {
            std::cerr << err << std::endl;
        }
    });
}

void  Babel::Networking::Session::write()
{
    asio::write(*_socket, asio::buffer(_data));
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