#pragma once

#include <memory>
#include "Database.hpp"

namespace Babel {
    namespace Database {
        class IModel {
        public:
            virtual void save(const Database &db) = 0;
            virtual void getById(const Database &db, int id) = 0;
            virtual void del(const Database &db) = 0;
        };
    }
}


