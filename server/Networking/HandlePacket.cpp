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
#include <Networking/PacketTypes.hpp>
#include <Networking/Packets/PacketRespListInvites.hpp>
#include <Networking/Packets/PacketCmdAcceptFriend.hpp>
#include <Networking/Packets/PacketRespAcceptFriend.hpp>
#include <Networking/Packets/PacketCmdDenyFriend.hpp>
#include <Networking/Packets/PacketRespDenyFriend.hpp>
#include <Networking/Packets/PacketRespListFriends.hpp>
#include <Networking/Packets/PacketInviteReceived.hpp>
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
     } catch (std::runtime_error &err) {
        e = err.what();
        ok = 0;
     }

     if (e == "" && usr.getPassword() != cmdLoginPacket->getPassword()) {
         e = "Invalid password.";
         ok = 0;
     }

    Babel::Networking::Packets::PacketRespLogin resp(ok, e, usr.getId());
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
    catch (std::runtime_error &err) {}
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
    } catch (std::runtime_error &err) {
        Babel::Networking::Packets::PacketRespInviteFriend resp{0, "Could not find user.", 0, ""};
        return resp.serialize();
    }

    if (newFriend.getId() == session->getUserId()) {
        Babel::Networking::Packets::PacketRespInviteFriend resp{0, "You can't invite yourself.", 0, ""};
        return resp.serialize();
    }

    auto friends = Database::Friendship::getAllFriends(*db, session->getUserId());
    for (auto &fri : friends) {
        if (fri.getTo() == newFriend.getId() || fri.getFrom() == newFriend.getId()) {
            Babel::Networking::Packets::PacketRespInviteFriend resp{0, "Already a friend of yours.", 0, ""};
            return resp.serialize();
        }
    }

    auto invites = Database::Friendship::getAllWaiting(*db, session->getUserId());
    for (auto &fri : invites) {
        if (fri.getTo() == newFriend.getId() || fri.getFrom() == newFriend.getId()) {
            Babel::Networking::Packets::PacketRespInviteFriend resp{0, "An invite is already waiting.", 0, ""};
            return resp.serialize();
        }
    }

    Database::Friendship friendship;
    friendship.setFrom(session->getUserId());
    friendship.setTo(newFriend.getId());
    friendship.save(*db);

    auto otherSession = _server->getSessionFromUser(newFriend.getId());
    if (otherSession != nullptr) {
        Database::User self;
        self.getById(*db, session->getUserId());

        Babel::Networking::Packets::PacketInviteReceived resp{friendship.getId(), self.getUsername()};
        otherSession->write(resp.serialize());
    }

    Babel::Networking::Packets::PacketRespInviteFriend resp{1, "", friendship.getId(), newFriend.getUsername()};
    return resp.serialize();
}

Babel::Networking::RawPacket
Babel::Networking::HandlePacket::handleCmdListInvites(Babel::Networking::RawPacket rawPacket,
                                                      Babel::Networking::Session *session) {
    auto db = _server->getDb();
    std::vector<Babel::Networking::Invite> netInvites;

    Database::User from;
    Database::User to;

    auto invites = Database::Friendship::getAllWaiting(*db, session->getUserId());
    for (auto &fri : invites) {
        from.getById(*db, fri.getFrom());
        to.getById(*db, fri.getTo());

        Babel::Networking::Invite netInvite;
        netInvite.id = fri.getId();
        netInvite.from = fri.getFrom();
        netInvite.fromUsername = from.getUsername();
        netInvite.toUsername = to.getUsername();
        netInvites.push_back(netInvite);
    }

    Babel::Networking::Packets::PacketRespListInvites resp{netInvites};
    return resp.serialize();
}

Babel::Networking::RawPacket
Babel::Networking::HandlePacket::handleCmdAcceptFriend(Babel::Networking::RawPacket rawPacket,
                                                       Babel::Networking::Session *session) {
    auto packet = std::static_pointer_cast<Babel::Networking::Packets::PacketCmdAcceptFriend>(rawPacket.deserialize());
    auto db = _server->getDb();

    Database::Friendship friendship;

    try {
        friendship.getById(*db, packet->getId());
    } catch (std::runtime_error &e) {
        Babel::Networking::Packets::PacketRespAcceptFriend resp{0, "Invite not found.", packet->getId(), 0, ""};
        return resp.serialize();
    }

    if (friendship.getTo() != session->getUserId()) {
        Babel::Networking::Packets::PacketRespAcceptFriend resp{0, "This invite is not for you.", packet->getId(), 0,  ""};
        return resp.serialize();
    }


    friendship.accept();
    friendship.save(*db);

    Database::User from;
    from.getById(*db, friendship.getFrom());

    Babel::Networking::Packets::PacketRespAcceptFriend resp{1, "", packet->getId(), from.getId(), from.getUsername()};
    return resp.serialize();
}

Babel::Networking::RawPacket
Babel::Networking::HandlePacket::handleCmdDenyFriend(Babel::Networking::RawPacket rawPacket,
                                                     Babel::Networking::Session *session) {
    auto packet = std::static_pointer_cast<Babel::Networking::Packets::PacketCmdDenyFriend>(rawPacket.deserialize());
    auto db = _server->getDb();

    Database::Friendship friendship;

    try {
        friendship.getById(*db, packet->getId());
    } catch (std::runtime_error &e) {
        Babel::Networking::Packets::PacketRespDenyFriend resp{0, "Invite not found.", packet->getId()};
        return resp.serialize();
    }

    if (friendship.getTo() != session->getUserId()) {
        Babel::Networking::Packets::PacketRespDenyFriend resp{0, "This invite is not for you.", packet->getId()};
        return resp.serialize();
    }

    friendship.del(*db);
    Babel::Networking::Packets::PacketRespDenyFriend resp{1, "", packet->getId()};
    return resp.serialize();
}

Babel::Networking::RawPacket
Babel::Networking::HandlePacket::handleCmdListFriends(Babel::Networking::RawPacket rawPacket,
                                                      Babel::Networking::Session *session) {
    auto db = _server->getDb();
    std::vector<Babel::Networking::User> netUsers;

    Database::User user;

    auto friends = Database::Friendship::getAllFriends(*db, session->getUserId());
    for (auto &fri : friends) {
        user.getById(*db, fri.getTo() == session->getUserId() ? fri.getFrom() : fri.getTo());

        Babel::Networking::User netUser;
        netUser.id = user.getId();
        netUser.username = user.getUsername();
        netUsers.push_back(netUser);
    }

    Babel::Networking::Packets::PacketRespListFriends resp{netUsers};
    return resp.serialize();
}
