/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Session
*/

#ifndef SESSION_HPP_
#define SESSION_HPP_

#include "asio.hpp"
#include <string>
#include <iostream>

namespace Babel {
    namespace Networking {
        class Session : public std::enable_shared_from_this<Session>{
            public:
                Session(std::shared_ptr<asio::ip::tcp::socket> socket);
                Session(const Session &session);

                std::shared_ptr<asio::ip::tcp::socket> getSocket() const;
                void setSocket(const std::shared_ptr<asio::ip::tcp::socket> socket);
                std::shared_ptr<asio::streambuf> getStreambuf() const;
                void setStreambuf(const std::shared_ptr<asio::streambuf> streambuffer);


                ~Session();

                void start();
            protected:
            private:
                std::shared_ptr<asio::ip::tcp::socket> _socket;
                std::shared_ptr<asio::streambuf>  _streambuf;

                void write();
                void read();
        };
    }
}

#endif /* !SESSION_HPP_ */
