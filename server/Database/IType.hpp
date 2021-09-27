#pragma once

#include <memory>
#include "Database.hpp"

namespace Babel {
    namespace Database {
        class IType {
        public:
            virtual void save(const Database &db) = 0;
            virtual void getById(const Database &db, int id) = 0;
        };
    }
}


