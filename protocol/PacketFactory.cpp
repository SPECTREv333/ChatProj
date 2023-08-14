//
// Created by Leonardo on 13/08/23.
//

#include "PacketFactory.h"
#include "concrete_packets/SignUp.h"
#include "concrete_packets/SignIn.h"
#include "concrete_packets/SignXResponse.h"

Packet *PacketFactory::decode(const std::string &raw) {
    Packet* decoded = nullptr;
    std::string::size_type pos = raw.find(':');
    std::string type = raw.substr(0, pos);

    if (type == SignUp::headerString){
        decoded = new SignUp();
    } else if (type == SignIn::headerString){
        decoded = new SignIn();
    } else if (type == SignXResponse::headerString){
        decoded = new SignXResponse();
    }

    if (decoded) {
        decoded->decode(raw);
    }
    return decoded;
}
