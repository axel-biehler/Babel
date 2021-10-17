//
// Created by axel on 13/10/2021.
//

#include <vector>
#include <iostream>
#include "Message.hpp"
#include <chrono>

Babel::Database::Message::Message() : _id(-1) {

}

void Babel::Database::Message::save(const Babel::Database::Database &db) {
    auto sqlite{db.getHandle()};
    const auto p1 = std::chrono::system_clock::now();

    if (_id < 0) {
        _timestamp = std::time(0);
        std::string query{"INSERT INTO Messages (body, \"to\", \"from\", status, timestamp) VALUES ('" +  _body + "', '" + std::to_string(_to) +
                          "', '" + std::to_string(_from) + "', '" + std::to_string(_status) + "', '" + std::to_string(_timestamp) +"')"};
        sqlite3_exec(sqlite, query.c_str(), nullptr, 0, nullptr);
        _id = sqlite3_last_insert_rowid(sqlite);
    } else {
        std::string query{"UPDATE Messages SET id = " + std::to_string(_id) + ", body = '" + _body +
                          "', \"to\" = '" + std::to_string(_to) + "', \"from\" = '" + std::to_string(_from)
                          + "', status = '" + std::to_string(_status) + "' WHERE id = " + std::to_string(_id)};
        sqlite3_exec(sqlite, query.c_str(), nullptr, 0, nullptr);
    }
}
    void Babel::Database::Message::getById(const Babel::Database::Database &db, int id) {
        auto sqlite{db.getHandle()};

        sqlite3_stmt *stmt;
        std::string query{"SELECT * FROM Messages WHERE id =" + std::to_string(id)};

        sqlite3_prepare_v2(sqlite, query.c_str(), -1, &stmt, nullptr);
        if (sqlite3_step(stmt) != SQLITE_ROW)
            throw std::runtime_error("Messages not found");
        _id = sqlite3_column_int(stmt, 0);
        _body = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        _to = sqlite3_column_int(stmt, 2);
        _from = sqlite3_column_int(stmt, 3);
        _status = sqlite3_column_int(stmt, 4);
        _timestamp = sqlite3_column_int(stmt, 5);
        sqlite3_finalize(stmt);
    }

void Babel::Database::Message::del(const Babel::Database::Database &db) {
    auto sqlite{db.getHandle()};

    if (_id < 0)
        return;
    std::string query{"DELETE FROM Messages WHERE id = " + std::to_string(_id)};
    sqlite3_exec(sqlite, query.c_str(), nullptr, 0, nullptr);
}

std::vector<Babel::Database::Message> Babel::Database::Message::getByConversation(const Babel::Database::Database &db, int uid) {
    auto sqlite{db.getHandle()};
    std::vector<Message> messages;

    sqlite3_stmt *stmt;
    std::string query{"SELECT * FROM Messages WHERE \"to\" = " + std::to_string(uid) + " OR " + "\"from\" = " + std::to_string(uid)    };

    sqlite3_prepare_v2(sqlite, query.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Message message;
        message.setId(sqlite3_column_int(stmt, 0));
        message.setBody(std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1))));
        message.setTo(sqlite3_column_int(stmt, 2));
        message.setFrom(sqlite3_column_int(stmt, 3));
        message.setStatus(sqlite3_column_int(stmt, 4));
        message.setTimestamp(sqlite3_column_int(stmt, 5));

        messages.push_back(message);
    }
    return messages;
}

    void Babel::Database::Message::setId(int id) {
    _id = id;
}

void Babel::Database::Message::setBody(std::string body) {
    _body = body;
}

void Babel::Database::Message::setTo(int to) {
    _to = to;
}

void Babel::Database::Message::setFrom(int from) {
    _from = from;
}

void Babel::Database::Message::setStatus(int status) {
    _status = status;
}

void Babel::Database::Message::setTimestamp(unsigned long timestamp) {
    _timestamp = timestamp;
}

std::string Babel::Database::Message::getBody() const {
    return _body;
}

int Babel::Database::Message::getTo() const {
    return _to;
}

int Babel::Database::Message::getFrom() const {
    return _from;
}

int Babel::Database::Message::getId() const {
    return _id;
}

int Babel::Database::Message::getStatus() const {
    return _status;
}

unsigned long Babel::Database::Message::getTimestamp() const {
    return _timestamp;
}

Babel::Database::Message::Message(Babel::Networking::Message message) : _id(message.id), _body(message.body), _to(message.to),
    _from(message.from), _status(message.status), _timestamp(message.timestamp) {

}


