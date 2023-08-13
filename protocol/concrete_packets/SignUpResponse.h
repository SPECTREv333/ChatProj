//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_SIGNUPRESPONSE_H
#define CHATPROJ_SIGNUPRESPONSE_H

#include "../Packet.h"

class SignUpResponse : public Packet {
public:
    SignUpResponse() = default;

    explicit SignUpResponse(int uniqueId, bool success) : uniqueId(uniqueId), success(success) {};

    std::string encode() override{
        std::string raw = headerString + ":";
        raw += std::to_string(uniqueId) + ":";
        raw += success ? "1" : "0";
        return raw;
    };

    void decode(const std::string& raw) override{
        std::string::size_type pos = raw.find(':') + 1;
        std::string::size_type pos2 = raw.find(':', pos);
        uniqueId = std::stoi(raw.substr(pos, pos2 - pos));
        success = raw.substr(pos2 + 1) == "1";
    };

    static inline std::string headerString = "signupresponse";
private:
    int uniqueId;
    bool success;
};


#endif //CHATPROJ_SIGNUPRESPONSE_H
