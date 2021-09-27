#include <iostream>
#include "User.hpp"

Babel::Database::User::User() : _id(-1) {
}

void Babel::Database::User::save(const Babel::Database::Database &db) {
    auto sqlite{db.getHandle()};

    if (_id < 0) {
        std::string query{"INSERT INTO Users (username) VALUES ('" +  _username + "')"};
        sqlite3_exec(sqlite, query.c_str(), nullptr, 0, nullptr);
        _id = sqlite3_last_insert_rowid(sqlite);
    } else {
        std::string query{"UPDATE Users SET id = " + std::to_string(_id) + ", username = '" + _username + "' WHERE id = " + std::to_string(_id)};
        sqlite3_exec(sqlite, query.c_str(), nullptr, 0, nullptr);
    }
}

void Babel::Database::User::getById(const Babel::Database::Database &db, int id) {
    auto sqlite{db.getHandle()};

    sqlite3_stmt *stmt;
    std::string query{"SELECT * FROM Users WHERE id=" + std::to_string(id)};

    sqlite3_prepare_v2(sqlite, query.c_str(), -1, &stmt, nullptr);
    if (sqlite3_step(stmt) != SQLITE_ROW)
        throw std::runtime_error("User not found");
    _id = sqlite3_column_int(stmt, 0);
    _username = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    sqlite3_finalize(stmt);
}

std::string Babel::Database::User::getUsername() const {
    return _username;
}

int Babel::Database::User::getId() const {
    return _id;
}

