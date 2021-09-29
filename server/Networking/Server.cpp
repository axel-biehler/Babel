/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Server
*/

#include "Server.hpp"

Babel::Networking::Server::Server(asio::io_context& io_context, short port) : _acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), _io_context(io_context)
{
}

Babel::Networking::Server::~Server()
{
}

void Babel::Networking::Server::async_accept()
{
    auto socket_ptr = std::make_shared<asio::ip::tcp::socket>(_io_context);

    _acceptor.async_accept(*socket_ptr, [&, socket_ptr] (std::error_code err)
    {
        if (!err) {
            std::cout << "connected" << std::endl;
            Babel::Networking::Session session(socket_ptr);
            session.start();
            _sessions.push_back(std::make_shared<Babel::Networking::Session>(session));
            async_accept();
        } else {
            std::cerr << err << std::endl;
        }
    });
}
