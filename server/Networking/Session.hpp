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
#include <Networking/RawPacket.hpp>

namespace Babel {
    namespace Networking {
        class Session : public std::enable_shared_from_this<Session> {
            public:
                Session(std::shared_ptr<asio::ip::tcp::socket> socket);
                Session(const Session &session);

                std::shared_ptr<asio::ip::tcp::socket> getSocket() const;
                char *getDate() const;

                ~Session();


                void start();
            private:
                std::shared_ptr<asio::ip::tcp::socket> _socket;
                char *_data;
                std::vector<char> _buffer;

                //method
                void write();
                void on_read(std::error_code error, std::size_t bytes_transferred);
                void on_write(std::error_code error, std::size_t bytes_transferred);
                void read();
                void handle_packet(Babel::Networking::RawPacket packet);

        };
    }
}

#endif /* !SESSION_HPP_ */
