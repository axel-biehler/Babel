/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Server
*/

#include "Server.hpp"

Babel::Networking::Server::Server(asio::io_context& io_context, short port, std::shared_ptr<Babel::Database::Database> db) :
    _acceptor(io_context,asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
    _io_context(io_context),
    _db(db)
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
            auto session = std::make_shared<Babel::Networking::Session>(socket_ptr, _handlePacket);
            session->start();
            _sessions.push_back(session);
            async_accept();
        } else {
            std::cerr << err << std::endl;
        }
    });
}

std::shared_ptr<Babel::Database::Database> Babel::Networking::Server::getDb() const
{
    return _db;
}

void Babel::Networking::Server::setHandlePacket(std::shared_ptr<Babel::Networking::IHandlePacket> handlePacket)
{
    _handlePacket = handlePacket;
}

std::shared_ptr<Babel::Networking::IHandlePacket> Babel::Networking::Server::getHandlePacket() const
{
    return _handlePacket;
}

std::shared_ptr<Babel::Networking::Session> Babel::Networking::Server::getSessionFromUser(int userId) {
    for (auto &session : _sessions)
        if (session->getUserId() == userId && !session->getIsClosed())
            return session;
    return nullptr;
}
