//
// Created by Leonardo on 14/08/23.
//

#ifndef CHATPROJ_SIGNOUT_H
#define CHATPROJ_SIGNOUT_H


#include <string>
#include "Packet.h"

class SignOut : public Packet {

public:
    SignOut() = default;

    SignOut(int UserId) {
        this->UserId = UserId;
    };

    std::string encode() override {
        std::string raw = headerString + ":";
        raw += std::to_string(UserId);
        return raw;
    };

    void decode(const std::string &raw) override {
        std::string::size_type pos = raw.find(':') + 1;
        UserId = std::stoi(raw.substr(pos));
    };

    const std::string &getHeader() const override {
        return headerString;
    };

    inline static const std::string headerString = "signout";
private:
    int UserId;

};


#endif //CHATPROJ_SIGNOUT_H
