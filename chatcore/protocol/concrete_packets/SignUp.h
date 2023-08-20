//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_SIGNUP_H
#define CHATPROJ_SIGNUP_H

#include "../Packet.h"

class SignUp : public Packet {

public:
    SignUp() = default;

    SignUp(const std::string &username, const std::string &password) {
        this->username = username;
        this->password = password;
    };

    std::string encode() override {
        std::string raw = headerString + ":";
        raw += username + ":";
        raw += password;
        return raw;
    };

    void decode(const std::string &raw) override {
        std::string::size_type pos = raw.find(':') + 1;
        std::string::size_type pos2 = raw.find(':', pos);
        username = raw.substr(pos, pos2 - pos);
        password = raw.substr(pos2 + 1);
    };

    const std::string &getUsername() const {
        return username;
    };

    const std::string &getPassword() const{
        return password;
    };

    const std::string &getHeader() const override {
        return headerString;
    };

    inline static const std::string headerString = "signup";
private:
    std::string username;

    std::string password;

};


#endif //CHATPROJ_SIGNUP_H
