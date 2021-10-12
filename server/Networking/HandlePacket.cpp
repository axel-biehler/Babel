//
// Created by axel on 11/10/2021.
//

#include <Networking/Packets/PacketCmdLogin.hpp>
#include <Database/User.hpp>
#include <Networking/Packets/PacketRespLogin.hpp>
#include <Networking/Packets/PacketRespRegister.hpp>
#include <Networking/Packets/PacketCmdRegister.hpp>
#include "HandlePacket.hpp"

Babel::Networking::HandlePacket::HandlePacket(std::shared_ptr<Server> server) : _server(server)
{
}

Babel::Networking::RawPacket Babel::Networking::HandlePacket::handleCmdLoginPacket(RawPacket packet, Session *session)
{
    auto cmdLoginPacket = std::static_pointer_cast<Babel::Networking::Packets::PacketCmdLogin>(packet.deserialize());
    Babel::Database::User usr;
    char ok = 1;
    std::string e = "";
    std::shared_ptr<Babel::Database::Database> db = _server->getDb();

     try {
         usr.getByUsername(*db, cmdLoginPacket->getUsername());
     } catch (std::runtime_error err) {
        e = err.what();
        ok = 0;
     }

     if (e == "" && usr.getPassword() != cmdLoginPacket->getPassword()) {
         e = "Invalid password.";
         ok = 0;
     }

    Babel::Networking::Packets::PacketRespLogin resp(ok, e);
    session->setUserId(usr.getId());
    return resp.serialize();
}

Babel::Networking::RawPacket Babel::Networking::HandlePacket::handleCmdRegisterPacket(RawPacket rawPacket, Session *session)
{
    auto cmdRegisterPacket = std::static_pointer_cast<Babel::Networking::Packets::PacketCmdRegister>(rawPacket.deserialize());
    Babel::Database::User usr;
    std::shared_ptr<Babel::Database::Database> db = _server->getDb();

    try {
        usr.getByUsername(*db, cmdRegisterPacket->getUsername());
    }
    catch (std::runtime_error err) {}
    if (usr.getUsername() == cmdRegisterPacket->getUsername()) {
        Babel::Networking::Packets::PacketRespRegister resp(0, "Username already used.");
        return resp.serialize();
    }
    usr.setUsername(cmdRegisterPacket->getUsername());
    usr.setPassword(cmdRegisterPacket->getPassword());

    usr.save(*db);
    Babel::Networking::Packets::PacketRespRegister resp(1, "");
    return resp.serialize();
}