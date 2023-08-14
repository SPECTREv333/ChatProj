//
// Created by Leonardo on 13/08/23.
//

#include "PacketFactory.h"
#include "concrete_packets/SignUp.h"

Packet *PacketFactory::decode(std::string raw) {
    Packet* decoded;
    std::string::size_type pos = raw.find(':');
    std::string type = raw.substr(0, pos);
    if (type == SignUp::headerString){
        decoded = new SignUp();
        decoded->decode(raw);
        return decoded;
    }
    return nullptr;
}
