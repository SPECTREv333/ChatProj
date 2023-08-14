//
// Created by Leonardo on 13/08/23.
//

#include "ChatAPI.h"
#include "../network/SimpleSocket.h"
#include "Packet.h"
#include "concrete_packets/SignUp.h"
#include "concrete_packets/SignXResponse.h"
#include "PacketFactory.h"
#include "concrete_packets/SignIn.h"
#include "concrete_packets/SignOut.h"

//TODO: signX methods code duplication, refactor if possible

ChatAPI::ChatAPI() {
    socket = new SimpleSocket();
}

bool ChatAPI::signUp(const std::string &nickname, const std::string &password) {
    Packet* packet = new SignUp(nickname, password);
    socket->write(packet->encode());
    delete packet;
    std::string raw = socket->syncread();
    packet = PacketFactory::decode(raw);
    SignXResponse *response = nullptr;
    if (packet && packet->getHeader() == SignXResponse::headerString)
        response = reinterpret_cast<SignXResponse*>(packet);

    if (response && response->isSuccess()){
        currentUser.setNickname(nickname);
        currentUser.setId(response->getUniqueId());
        delete response;
        return true;
    }
    delete packet;
    return false;
}

bool ChatAPI::signIn(const std::string &nickname, const std::string &password) {
    Packet* packet = new SignIn(nickname, password);
    socket->write(packet->encode());
    delete packet;
    std::string raw = socket->syncread();
    packet = PacketFactory::decode(raw);
    SignXResponse *response = nullptr;
    if (packet && packet->getHeader() == SignXResponse::headerString)
        response = reinterpret_cast<SignXResponse*>(packet);

    if (response && response->isSuccess()){
        currentUser.setNickname(nickname);
        currentUser.setId(response->getUniqueId());
        return true;
    }
    return false;
}

bool ChatAPI::signOut() {
    Packet* packet = new SignOut(currentUser.getId());
    socket->write(packet->encode());
    delete packet;
    std::string raw = socket->syncread();
    packet = PacketFactory::decode(raw);
    SignXResponse *response = nullptr;
    if (packet && packet->getHeader() == SignXResponse::headerString)
        response = reinterpret_cast<SignXResponse*>(packet);

    if (response && response->isSuccess()){
        return true;
    }
    return false;
}


