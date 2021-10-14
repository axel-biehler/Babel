/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "asio.hpp"
#include "Session.hpp"
#include "IHandlePacket.hpp"
#include "Call.hpp"
#include <optional>
#include <vector>
#include <Database/Database.hpp>

namespace Babel {
    namespace Networking {

        class Server {
            public:
                Server(asio::io_context& io_context, short port, std::shared_ptr<Babel::Database::Database> db);
                ~Server();

                void async_accept();
                std::shared_ptr<Babel::Database::Database> getDb() const;
                void setHandlePacket(std::shared_ptr<Babel::Networking::IHandlePacket> handlePacket);
                std::shared_ptr<Babel::Networking::IHandlePacket> getHandlePacket() const;

                std::shared_ptr<Babel::Networking::Session> getSessionFromUser(int userId);
                void addCall(int from, int to);
                void validateCall(int from, int to);

            private:
                asio::ip::tcp::acceptor _acceptor;
                asio::io_context& _io_context;
                std::vector<std::shared_ptr<Babel::Networking::Session>> _sessions;
                std::shared_ptr<Babel::Database::Database> _db;
                std::shared_ptr<Babel::Networking::IHandlePacket> _handlePacket;
                std::vector<Call> _calls;
        };
    }
}

#endif /* !SERVER_HPP_ */
