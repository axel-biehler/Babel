#pragma once

#include <string>
#include "IType.hpp"

namespace Babel {
    namespace Database {
        class User : public IType {
        public:
            User();

            void save(const Database &db) override;
            void getById(const Database &db, int id) override;

            int getId() const;
            std::string getUsername() const;

            int _id;
            std::string _username;
        };
    }
}