//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_PACKETFACTORY_H
#define CHATPROJ_PACKETFACTORY_H

#include "Packet.h"

class PacketFactory {
public:
    static Packet *decode(std::string raw);
};


#endif //CHATPROJ_PACKETFACTORY_H
