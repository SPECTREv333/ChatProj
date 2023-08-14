//
// Created by Leonardo on 14/08/23.
//

#ifndef CHATPROJ_USERLIST_H
#define CHATPROJ_USERLIST_H

#include "Packet.h"

class UserList : public Packet {
public:
    UserList() = default;

    std::string encode() override {
        return headerString + ":";
    };

    void decode(const std::string &raw) override {};

    const std::string& getHeader() const override {
        return headerString;
    };

    inline static const std::string headerString = "userlist";
private:
};

#endif //CHATPROJ_USERLIST_H
