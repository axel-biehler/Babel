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
#include <optional>

namespace Babel {
    namespace Networking {
        class Server {
            public:
                Server(asio::io_context& io_context, short port);
                ~Server();

                void async_accept();


        protected:
            private:
                asio::ip::tcp::acceptor _acceptor;
                asio::io_context& _io_context;
                std::optional<asio::ip::tcp::socket> _socket;
        };
    }
}

#endif /* !SERVER_HPP_ */
