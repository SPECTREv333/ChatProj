//
// Created by Leonardo on 14/08/23.
//

#ifndef CHATPROJ_MESSAGEPACKET_H
#define CHATPROJ_MESSAGEPACKET_H


#include "Packet.h"

class MessagePacket : public Packet {

public:
    MessagePacket() = default; //TODO: maybe initialize senderId and receiverId

    MessagePacket(int senderId, int receiverId, const std::string &message) {
        this->senderId = senderId;
        this->receiverId = receiverId;
        this->message = message;
    };

    std::string encode() override {
        std::string raw = headerString + ":";
        raw += std::to_string(senderId) + ":";
        raw += std::to_string(receiverId) + ":";
        raw += message;
        return raw;
    };

    void decode(const std::string &raw) override {
        std::string::size_type pos = raw.find(':') + 1;
        std::string::size_type pos2 = raw.find(':', pos);
        senderId = std::stoi(raw.substr(pos, pos2 - pos));
        pos = pos2 + 1;
        pos2 = raw.find(':', pos);
        receiverId = std::stoi(raw.substr(pos, pos2 - pos));
        message = raw.substr(pos2 + 1);
    };

    int getSenderId() const {
        return senderId;
    };

    int getReceiverId() const {
        return receiverId;
    };

    const std::string &getMessage() const {
        return message;
    };

    const std::string &getHeader() const override {
        return MessagePacket::headerString;
    };

    inline static const std::string headerString = "message";
private:
    int senderId;

    int receiverId;

    std::string message;
};


#endif //CHATPROJ_MESSAGEPACKET_H
