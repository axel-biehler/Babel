#pragma once

#include <string>
#include <vector>
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
            Friendship(int id, int from, int to, FriendshipStatus status);

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

            static std::vector<Friendship> getAllFriends(const Babel::Database::Database &db, int userId);
            static std::vector<Friendship> getAllWaiting(const Babel::Database::Database &db, int userId);

            int _id;
            int _from;
            int _to;
            FriendshipStatus _status;
        };
    }
}