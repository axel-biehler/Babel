#pragma once

#include <string>
#include "IModel.hpp"

namespace Babel {
    namespace Database {
        class User : public IModel {
        public:
            User();

            void save(const Database &db) override;
            void getById(const Database &db, int id) override;
            void del(const Database &db) override;

            int getId() const;
            std::string getUsername() const;

            int _id;
            std::string _username;
        };
    }
}