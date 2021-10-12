#pragma once

#include <string>
#include "IModel.hpp"

namespace Babel {
    namespace Database {
        enum FriendshipStatus {
            Waiting,
            Accepted,
        };

        class Friendship : public IModel {
        public:
            Friendship();

            void save(const Database &db) override;
            void getById(const Database &db, int id) override;
            void del(const Database &db) override;

            int getId() const;
            int getFrom() const;
            int getTo() const;
            FriendshipStatus getStatus() const;
            void setFrom(int from);
            void setTo(int to);
            void accept();

        private:
            int _id;
            int _from;
            int _to;
            FriendshipStatus _status;
        };
    }
}