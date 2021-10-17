/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-alexandre.sauner
** File description:
** Session
*/

#include "Session.hpp"
#include <Networking/RawPacket.hpp>
#include <Networking/RawTypes.hpp>
#include <Networking/Packets/PacketCmdLogin.hpp>
#include <Networking/Packets/PacketRespLogin.hpp>
#include <utility>

Babel::Networking::Session::Session(std::shared_ptr<asio::ip::tcp::socket> socket, std::shared_ptr<Babel::Networking::IHandlePacket> handlePacket) :
    _socket(socket), _handlePacket(handlePacket), _isClosed(false)
{
    _data = (char *)(malloc(1024));
    _size_str = (char *)(malloc(4));
}

Babel::Networking::Session::Session(const Session &session) : _socket(session.getSocket()), _handlePacket(session.getHandlePacket()), _isClosed(false)
{
    _data = (char *)(malloc(1024));
    _size_str = (char *)(malloc(4));
}

Babel::Networking::Session::~Session()
{
    free(_data);
    free(_size_str);
}

void Babel::Networking::Session::start()
{
    read();
}


void Babel::Networking::Session::read()
{
    _socket->async_receive( asio::buffer(_size_str, 4), std::bind(&Session::on_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void Babel::Networking::Session::on_read(std::error_code error, std::size_t bytes_transferred)
{
    if(error) {
        _isClosed = true;
        return;
    }
    try {
        RawInt raw{};
        for (int i = 0; i < sizeof(raw.i); i++)
            raw.c[i] = _size_str[i];
        _size = raw.i - 4;
        _socket->async_receive(asio::buffer(_data, _size), std::bind(&Session::on_read_data, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }
    catch (std::invalid_argument err) {
        std::cerr << err.what() << std::endl;
    }
}

void Babel::Networking::Session::on_read_data(std::error_code error, std::size_t bytes_transferred)
{
    if (error) {
        _isClosed = true;
        return;
    }
    for (int i = 0; i < 4; i++)
        _buffer.push_back(_size_str[i]);
    for (int i = 0; i < _size; i++)
        _buffer.push_back(_data[i]);
    auto rawPacket = Babel::Networking::RawPacket(_buffer);
    handle_packet(rawPacket);
    _buffer.clear();
    read();
}

void Babel::Networking::Session::handle_packet(Babel::Networking::RawPacket rawPacket) {
    switch (rawPacket.getPacketType()) {
        case Babel::Networking::PacketType::PacketCmdLogin:
            write(_handlePacket->handleCmdLoginPacket(rawPacket, this));
            break;
        case Babel::Networking::PacketType::PacketCmdRegister:
            write(_handlePacket->handleCmdRegisterPacket(rawPacket, this));
            break;
        case Babel::Networking::PacketType::PacketCmdInviteFriend:
            write(_handlePacket->handleCmdInviteFriendPacket(rawPacket, this));
            break;
        case Babel::Networking::PacketType::PacketCmdListInvites:
            write(_handlePacket->handleCmdListInvites(rawPacket, this));
            break;
        case Babel::Networking::PacketType::PacketCmdAcceptFriend:
            write(_handlePacket->handleCmdAcceptFriend(rawPacket, this));
            break;
        case Babel::Networking::PacketType::PacketCmdDenyFriend:
            write(_handlePacket->handleCmdDenyFriend(rawPacket, this));
            break;
        case Babel::Networking::PacketType::PacketCmdListFriends:
            write(_handlePacket->handleCmdListFriends(rawPacket, this));
            break;
        case Babel::Networking::PacketType::PacketCmdListMessages:
            write(_handlePacket->handleCmdListMessages(rawPacket, this));
            break;
        case Babel::Networking::PacketType::PacketMessageSend:
            _handlePacket->handleSendMessage(rawPacket,this);
            break;
    }
}

void Babel::Networking::Session::write(Babel::Networking::RawPacket rawPacket)
{
    auto data{rawPacket.toStdString()};
    _socket->send(asio::buffer(data, data.size()));
}

std::shared_ptr<asio::ip::tcp::socket> Babel::Networking::Session::getSocket() const
{
    return _socket;
}

std::shared_ptr<Babel::Networking::IHandlePacket> Babel::Networking::Session::getHandlePacket() const
{
    return _handlePacket;
}

void Babel::Networking::Session::setUserId(int userId)
{
    _userId = userId;
}

int Babel::Networking::Session::getUserId() const {
    return _userId;
}

bool Babel::Networking::Session::getIsClosed() const {
    return true;
}
