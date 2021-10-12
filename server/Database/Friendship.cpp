#include <iostream>
#include "Friendship.hpp"

Babel::Database::Friendship::Friendship() : _id(-1), _from(-1), _to(-1), _status(FriendshipStatus::Waiting) {
}

void Babel::Database::Friendship::save(const Babel::Database::Database &db) {
    auto sqlite{db.getHandle()};

    if (_id < 0) {
        std::string query{"INSERT INTO Friendships (from, to, status) VALUES (" +
                                  std::to_string(_from) + ", " + std::to_string(_to) + ", " +
                                  std::to_string(_status) + ")"};
        sqlite3_exec(sqlite, query.c_str(), nullptr, nullptr, nullptr);
        _id = sqlite3_last_insert_rowid(sqlite);
    } else {
        std::string query{"UPDATE Friendships SET id = " + std::to_string(_id) +
            ", from = " + std::to_string(_from) + ", to = " +
            std::to_string(_to) + ", status = " + std::to_string(_status) +
            " WHERE id = " + std::to_string(_id)};
        sqlite3_exec(sqlite, query.c_str(), nullptr, nullptr, nullptr);
    }
}

void Babel::Database::Friendship::getById(const Babel::Database::Database &db, int id) {
    auto sqlite{db.getHandle()};

    sqlite3_stmt *stmt;
    std::string query{"SELECT * FROM Friendships WHERE id=" + std::to_string(id)};

    sqlite3_prepare_v2(sqlite, query.c_str(), -1, &stmt, nullptr);
    if (sqlite3_step(stmt) != SQLITE_ROW)
        throw std::runtime_error("Friendship not found");
    _id = sqlite3_column_int(stmt, 0);
    _from = sqlite3_column_int(stmt, 1);
    _to = sqlite3_column_int(stmt, 2);
    _status = static_cast<FriendshipStatus>(sqlite3_column_int(stmt, 3));
    sqlite3_finalize(stmt);
}

void Babel::Database::Friendship::del(const Babel::Database::Database &db) {
    auto sqlite{db.getHandle()};

    if (_id < 0)
        return;
    std::string query{"DELETE FROM Friendships WHERE id = " + std::to_string(_id)};
    sqlite3_exec(sqlite, query.c_str(), nullptr, nullptr, nullptr);
}

int Babel::Database::Friendship::getId() const {
    return _id;
}

int Babel::Database::Friendship::getFrom() const {
    return _from;
}

int Babel::Database::Friendship::getTo() const {
    return _to;
}

Babel::Database::FriendshipStatus Babel::Database::Friendship::getStatus() const {
    return _status;
}

void Babel::Database::Friendship::setFrom(int from) {
    _from = from;
}

void Babel::Database::Friendship::setTo(int to) {
    _to = to;
}

void Babel::Database::Friendship::accept() {
    _status = FriendshipStatus::Accepted;
}
