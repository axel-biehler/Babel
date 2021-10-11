//
// Created by axel on 11/10/2021.
//

#include "HandlePacket.h"

Babel::Networking::HandlePacket::HandlePacket(std::shared_ptr<Babel::Networking::Session> session, std::shared_ptr<Babel::Database::Database> db) : _session(session), _db(db)
{

}

void Babel::Networking::HandlePacket::handleCmdLoginPacket(RawPacket packet)
{
    _db.
}