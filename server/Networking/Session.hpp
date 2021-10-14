/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Session
*/

#ifndef SESSION_HPP_
#define SESSION_HPP_

#include "asio.hpp"
#include "IHandlePacket.hpp"
#include <string>
#include <iostream>
#include <Networking/RawPacket.hpp>
#include <Database/Database.hpp>

namespace Babel {
    namespace Networking {
        class Session : public std::enable_shared_from_this<Session> {
            public:
                Session(std::shared_ptr<asio::ip::tcp::socket> socket, std::shared_ptr<Babel::Networking::IHandlePacket> handlePacket);
                Session(const Session &session);

                std::shared_ptr<asio::ip::tcp::socket> getSocket() const;
                std::shared_ptr<Babel::Networking::IHandlePacket> getHandlePacket() const;
                void setUserId(int userId);
                int getUserId() const;
                std::string getIp() const;

            ~Session();

                void start();
                void write(RawPacket packet);
            private:
                std::shared_ptr<asio::ip::tcp::socket> _socket;
                char *_data;
                std::vector<char> _buffer;
                char *_size_str;
                char _size;
                std::shared_ptr<Babel::Networking::IHandlePacket> _handlePacket;
                int _userId;

            //method
                void on_read(std::error_code error, std::size_t bytes_transferred);
                void on_read_data(std::error_code error, std::size_t bytes_transferred);
                void read();
                void handle_packet(Babel::Networking::RawPacket packet);
        };
    }
}

#endif /* !SESSION_HPP_ */
