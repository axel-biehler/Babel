#pragma once

#include <string>
#include <sqlite3.h>

namespace Babel {
    namespace Database {
        class Database {
        public:
            Database(const std::string &filename);
            ~Database();

            sqlite3 *getHandle() const;

        private:
            sqlite3 *_db;
        };

    }
}
