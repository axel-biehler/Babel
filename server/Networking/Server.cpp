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

    _socket.emplace(_io_context);

    _acceptor.async_accept(*_socket, [&] (std::error_code err)
    {
        std::make_shared<Babel::Networking::Session>(std::move(*_socket))->start();
        async_accept();
    });
}
