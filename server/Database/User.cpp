#include <iostream>
#include "User.hpp"

Babel::Database::User::User() : _id(-1) {
}

void Babel::Database::User::save(const Babel::Database::Database &db) {
    auto sqlite{db.getHandle()};

    if (_id < 0) {
        std::string query{"INSERT INTO Users (username, password) VALUES ('" +  _username + "', '" + _password + "')"};
        sqlite3_exec(sqlite, query.c_str(), nullptr, 0, nullptr);
        _id = sqlite3_last_insert_rowid(sqlite);
    } else {
        std::string query{"UPDATE Users SET id = " + std::to_string(_id) + ", username = '" + _username + "', password= '" + _password + "' WHERE id = " + std::to_string(_id)};
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
    _password = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    sqlite3_finalize(stmt);
}

void Babel::Database::User::getByUsername(const Babel::Database::Database &db, const std::string &name)
{
    auto sqlite{db.getHandle()};

    sqlite3_stmt *stmt;
    std::string query{"SELECT * FROM Users WHERE username='" + name + "'"};

    sqlite3_prepare_v2(sqlite, query.c_str(), -1, &stmt, nullptr);
    if (sqlite3_step(stmt) != SQLITE_ROW)
        throw std::runtime_error("User not found");
    _id = sqlite3_column_int(stmt, 0);
    _username = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    _password = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    sqlite3_finalize(stmt);
}

std::string Babel::Database::User::getUsername() const {
    return _username;
}

int Babel::Database::User::getId() const {
    return _id;
}

void Babel::Database::User::setUsername(const std::string &username) {
    _username = username;
}

void Babel::Database::User::del(const Babel::Database::Database &db) {
    auto sqlite{db.getHandle()};

    if (_id < 0)
        return;
    std::string query{"DELETE FROM Users WHERE id = " + std::to_string(_id)};
    sqlite3_exec(sqlite, query.c_str(), nullptr, 0, nullptr);
}

std::string Babel::Database::User::getPassword() const
{
    return _password;
}

void Babel::Database::User::setPassword(const std::string &pass)
{
    _password = pass;
}
