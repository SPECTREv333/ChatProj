//
// Created by Leonardo on 13/08/23.
//

#include "ChatAPI.h"
#include "Packet.h"
#include "concrete_packets/SignUp.h"
#include "concrete_packets/SignXResponse.h"
#include "PacketFactory.h"
#include "concrete_packets/SignIn.h"
#include "concrete_packets/SignOut.h"
#include "concrete_packets/MessagePacket.h"
#include "concrete_packets/UserList.h"
#include "concrete_packets/UserListResponse.h"
#include "../network/Socket.h"

//TODO: signX methods code duplication, refactor if possible

ChatAPI::ChatAPI(const std::string& address, int port) {
    socket = new Socket(address, port);
    socket->setMediator(this);
    lastMessage = nullptr;
}

ChatAPI::~ChatAPI() {
    delete socket;
}

void ChatAPI::signUp(const std::string &nickname, const std::string &password) {
    Packet *packet = new SignUp(nickname, password);
    socket->write(packet->encode());
    currentUser.setNickname(nickname);
    delete packet;
}

void ChatAPI::signIn(const std::string &nickname, const std::string &password) {
    Packet *packet = new SignIn(nickname, password);
    socket->write(packet->encode());
    currentUser.setNickname(nickname);
    delete packet;
}

void ChatAPI::signOut() {
    Packet *packet = new SignOut(currentUser.getId());
    socket->write(packet->encode());
    delete packet;
}

void ChatAPI::sendMessage(const Message &message) {
    Packet *packet = new MessagePacket(message.getSender().getId(), message.getReceiver().getId(),
                                       message.getContent());
    socket->write(packet->encode());
    delete packet;
}

Message *ChatAPI::receiveMessage() {
    return lastMessage;
}

void ChatAPI::newPacket() {
    std::string raw = socket->read();
    Packet *packet = PacketFactory::decode(raw);
    if (packet) {
        if (packet->getHeader() == SignXResponse::headerString) {
            handleSignXResponse(reinterpret_cast<SignXResponse *>(packet));
        } else if (packet->getHeader() == MessagePacket::headerString) {
            handleMessagePacket(reinterpret_cast<MessagePacket *>(packet));
        } else if (packet->getHeader() == UserListResponse::headerString) {
            handleUserListResponse(reinterpret_cast<UserListResponse *>(packet));
        }
    }
}

void ChatAPI::handleSignXResponse(SignXResponse *response) {
    if (response->isSuccess()) {
        currentUser.setId(response->getUniqueId());
        mediator->notify(this, "signedIn");
    } else {
        mediator->notify(this, "signInFailed");
    }
}

void ChatAPI::handleMessagePacket(MessagePacket *packet) {
    if (packet->getReceiverId() == currentUser.getId()) {
        if (users.find(packet->getSenderId()) == users.end())
            refreshUsers();

        if (users.find(packet->getSenderId()) == users.end()) //TODO: maybe extract to utility function
            return;

        lastMessage = new Message(users[packet->getSenderId()], users[packet->getReceiverId()], packet->getMessage());

        mediator->notify(this, "newMessage");
    }
}

void ChatAPI::handleUserListResponse(UserListResponse *packet) {
    for (const auto &user: packet->getUsers()) {
        users[user.getId()] = user;
    }
    mediator->notify(this, "userListUpdated");
}


void ChatAPI::refreshUsers() {
    Packet *packet = new UserList();
    socket->write(packet->encode());
    delete packet;
}

std::list<User> ChatAPI::getUsers() const {
    std::list<User> userList;
    for (const auto &user: users) {
        userList.push_back(user.second);
    }
    return userList;
}

const User &ChatAPI::getCurrentUser() const {
    return currentUser;
}

void ChatAPI::notify(Component *sender, const std::string &event) {
    if (socket == sender){
        if (event == "message"){
            newPacket();
        } else if (event == "disconnect"){
            mediator->notify(this, event);
        }
    }
}




