//
// Created by axel on 11/10/2021.
//

#include <Networking/Packets/PacketCmdLogin.hpp>
#include <Database/User.hpp>
#include <Database/Friendship.hpp>
#include <Networking/Packets/PacketRespLogin.hpp>
#include <Networking/Packets/PacketRespRegister.hpp>
#include <Networking/Packets/PacketCmdRegister.hpp>
#include <Networking/Packets/PacketCmdInviteFriend.hpp>
#include <Networking/Packets/PacketRespInviteFriend.hpp>
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
     if(usr.getPassword() != cmdLoginPacket->getPassword()) {
         ok = 0;
         e = "Invalid Password.";
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

Babel::Networking::RawPacket Babel::Networking::HandlePacket::handleCmdInviteFriendPacket(Babel::Networking::RawPacket rawPacket, Babel::Networking::Session *session) {
    auto packet = std::static_pointer_cast<Babel::Networking::Packets::PacketCmdInviteFriend>(rawPacket.deserialize());
    auto db = _server->getDb();

    Database::User newFriend;

    try {
        newFriend.getByUsername(*db, packet->getUsername());
    } catch (std::runtime_error err) {
        Babel::Networking::Packets::PacketRespInviteFriend resp{0, "Could not find user."};
        return resp.serialize();
    }

    auto friends = Database::Friendship::getAllFriends(*db, session->getUserId());
    for (auto fri : friends) {
        if (fri.getTo() == newFriend.getId() || fri.getFrom() == newFriend.getId()) {
            Babel::Networking::Packets::PacketRespInviteFriend resp{0, "Already a friend of yours."};
            return resp.serialize();
        }
    }

    auto invites = Database::Friendship::getAllWaiting(*db, session->getUserId());
    for (auto fri : invites) {
        if (fri.getTo() == newFriend.getId() || fri.getFrom() == newFriend.getId()) {
            Babel::Networking::Packets::PacketRespInviteFriend resp{0, "An invite is already waiting."};
            return resp.serialize();
        }
    }

    Database::Friendship friendship;
    friendship.setFrom(session->getUserId());
    friendship.setTo(newFriend.getId());
    friendship.save(*db);

    Babel::Networking::Packets::PacketRespInviteFriend resp{1, ""};
    return resp.serialize();
}
