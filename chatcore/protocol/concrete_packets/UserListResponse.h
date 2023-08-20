//
// Created by Leonardo on 14/08/23.
//

#ifndef CHATPROJ_USERLISTRESPONSE_H
#define CHATPROJ_USERLISTRESPONSE_H

#include "../model/User.h"
#include "Packet.h"
#include <vector>

class UserListResponse : public Packet {
public:
    UserListResponse() = default;

    UserListResponse(const std::vector<User> &users) {
        this->users = users;
    };

    std::string encode() override {
        std::string raw = headerString + ":";
        for (auto &user: users) {
            raw += std::to_string(user.getId()) + ":" + user.getNickname() + ";";
        }
        return raw;
    };

    void decode(const std::string &raw) override {
        //ignore packet headerString "userlist:"
        std::string::size_type pos = raw.find(':');
        std::string::size_type last_pos = pos + 1;
        //split on ';' creating a vector of strings
        std::vector<std::string> users_raw;
        while ((pos = raw.find(';', last_pos)) != std::string::npos) {
            users_raw.push_back(raw.substr(last_pos, pos - last_pos));
            last_pos = pos + 1;
        }
        //split on ':' creating a vector of users
        for (auto &user_raw: users_raw) {
            pos = user_raw.find(':');
            int id = std::stoi(user_raw.substr(0, pos));
            std::string nickname = user_raw.substr(pos + 1);
            users.emplace_back(id, nickname);
        }
    };

    const std::vector<User> &getUsers() const {
        return users;
    };

    const std::string& getHeader() const override {
        return headerString;
    };

    inline static const std::string headerString = "userlistresponse";
private:

    std::vector<User> users;
};


#endif //CHATPROJ_USERLISTRESPONSE_H
