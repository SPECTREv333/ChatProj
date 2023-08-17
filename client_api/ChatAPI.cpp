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
#include "concrete_packets/MessagePacket.h"
#include "concrete_packets/UserList.h"
#include "concrete_packets/UserListResponse.h"

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

void ChatAPI::sendMessage(const Message &message) {
    Packet* packet = new MessagePacket(message.getSender().getId(), message.getReceiver().getId(), message.getContent());
    socket->write(packet->encode());
    delete packet;
}

Message * ChatAPI::receiveMessage() {
    std::string raw = socket->read();
    Packet* packet = PacketFactory::decode(raw);
    MessagePacket *messagePacket = nullptr;
    if (packet && packet->getHeader() == MessagePacket::headerString)
        messagePacket = reinterpret_cast<MessagePacket*>(packet);

    if (!messagePacket || messagePacket->getReceiverId() != currentUser.getId())
        return nullptr;

    if (users.find(messagePacket->getSenderId()) == users.end())
        refreshUsers();

    if (users.find(messagePacket->getSenderId()) == users.end()) //TODO: maybe extract to utility function
        return nullptr;

    return new Message(users[messagePacket->getSenderId()], users[messagePacket->getReceiverId()], messagePacket->getMessage());
}

void ChatAPI::update() {
    if (mediator)
        mediator->notify(this, "newmessage");
}

bool ChatAPI::refreshUsers() {
    Packet* packet = new UserList();
    socket->write(packet->encode());
    delete packet;
    std::string raw = socket->syncread();
    packet = PacketFactory::decode(raw);
    UserListResponse *response = nullptr;
    if (packet && packet->getHeader() == UserListResponse::headerString)
        response = reinterpret_cast<UserListResponse*>(packet);

    if (response){
        for (const auto& user : response->getUsers()){
            users[user.getId()] = user;
        }
        return true;
    }
    delete packet;
    return false;
}

std::list<User> ChatAPI::getUsers() const {
    std::list<User> userList;
    for (const auto& user : users){
        userList.push_back(user.second);
    }
    return userList;
}




