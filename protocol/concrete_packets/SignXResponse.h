//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_SIGNXRESPONSE_H
#define CHATPROJ_SIGNXRESPONSE_H

#include "../Packet.h"

class SignXResponse : public Packet {
public:
    SignXResponse() = default;

    explicit SignXResponse(int uniqueId, bool success) : uniqueId(uniqueId), success(success) {};

    std::string encode() override {
        std::string raw = headerString + ":";
        raw += std::to_string(uniqueId) + ":";
        raw += success ? "1" : "0";
        return raw;
    };

    void decode(const std::string &raw) override {
        std::string::size_type pos = raw.find(':') + 1;
        std::string::size_type pos2 = raw.find(':', pos);
        uniqueId = std::stoi(raw.substr(pos, pos2 - pos));
        success = raw.substr(pos2 + 1) == "1";
    };

    const std::string &getHeader() const override{
        return headerString;
    };

    int getUniqueId() const {
        return uniqueId;
    }

    bool isSuccess() const {
        return success;
    }

    static inline std::string headerString = "signxresponse";
private:
    int uniqueId;
    bool success;
};


#endif //CHATPROJ_SIGNXRESPONSE_H
