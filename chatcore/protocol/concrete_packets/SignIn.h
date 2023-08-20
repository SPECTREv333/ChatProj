//
// Created by Leonardo on 14/08/23.
//

#ifndef CHATPROJ_SIGNIN_H
#define CHATPROJ_SIGNIN_H



#include "../Packet.h"

class SignIn : public Packet {

public:
    SignIn() = default;

    SignIn(const std::string &username, const std::string &password) {
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

    inline static const std::string headerString = "signin";
private:
    std::string username;

    std::string password;

};


#endif //CHATPROJ_SIGNIN_H
