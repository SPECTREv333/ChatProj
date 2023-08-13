//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_PACKET_H
#define CHATPROJ_PACKET_H

#include <string>

class Packet {
public:
    virtual ~Packet() = default;
    virtual std::string encode() = 0;
    virtual void decode(const std::string& raw) = 0;
    virtual const std::string& getHeader() const = 0;
};



#endif //CHATPROJ_PACKET_H
