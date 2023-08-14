//
// Created by Leonardo on 13/08/23.
//

#include "ChatAPI.h"
#include "../network/SimpleSocket.h"
#include "Packet.h"
#include "concrete_packets/SignUp.h"

ChatAPI::ChatAPI() {
    socket = new SimpleSocket();
}

bool ChatAPI::signUp(const std::string &nickname, const std::string &password) {
    Packet* packet = new SignUp(nickname, password);
    socket->write(packet->encode());
    delete packet;
    socket->syncread();
}


