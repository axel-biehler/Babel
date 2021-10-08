#include "Database.hpp"
#include <stdexcept>

Babel::Database::Database::Database(const std::string &filename) {
    sqlite3_initialize();
    int res{sqlite3_open(filename.c_str(), &_db)};

    if (res) throw std::runtime_error("Could not open database.");
}

Babel::Database::Database::~Database() {
    sqlite3_close(_db);
    sqlite3_shutdown();
}

sqlite3 *Babel::Database::Database::getHandle() const {
    return _db;
}
