//
// Created by axel on 13/10/2021.
//

#ifndef BABEL_MESSAGE_HPP
#define BABEL_MESSAGE_HPP

#include "IModel.hpp"

namespace Babel::Database {
    class Message : public IModel {
    public:
        Message();

        void save(const Database &db) override;
        void getById(const Database &db, int id) override;
        void del(const Database &db) override;

        void setId(int id);
        void setBody(std::string body);
        void setTo(int to);
        void setFrom(int from);
        void setStatus(int status);
        void setTimestamp(int timestamp);

        static std::vector<Message> getByConversation(const Database &db, int uid);
        int getId() const;
        std::string getBody() const;
        int getTo() const;
        int getFrom() const;
        int getStatus() const;
        int getTimestamp()const;

    private:
        int _id;
        std::string _body;
        int _from;
        int _to;
        int _status;
        int _timestamp;

    };
}

#endif //BABEL_MESSAGE_HPP
