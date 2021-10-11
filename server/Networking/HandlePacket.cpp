//
// Created by axel on 11/10/2021.
//

#include <Networking/Packets/PacketCmdLogin.hpp>
#include <Database/User.hpp>
#include <Networking/Packets/PacketRespLogin.hpp>
#include "HandlePacket.h"

Babel::Networking::HandlePacket::HandlePacket(std::shared_ptr<Babel::Database::Database> db) : _db(db)
{

}

Babel::Networking::RawPacket Babel::Networking::HandlePacket::handleCmdLoginPacket(RawPacket packet)
{
    auto cmdLoginPacket = std::static_pointer_cast<Babel::Networking::Packets::PacketCmdLogin>(packet.deserialize());
    Babel::Database::User usr;
    char ok = '1';
    std::string e = "";

     try {
         usr.getByUsername(*_db, cmdLoginPacket->getUsername());
     } catch (std::runtime_error err) {
        e = err.what();
        ok = '0';
     }
    Babel::Networking::Packets::PacketRespLogin resp(ok, e);
    return resp.serialize();
}