//
// Created by Leonardo on 15/08/23.
//

#include <iostream>
#include "ChatServer.h"
#include "../protocol/PacketFactory.h"
#include "concrete_packets/SignXResponse.h"
#include "concrete_packets/UserListResponse.h"

void ChatServer::handleSignUp(EventSocket *sender, SignUp *packet) {
    if (usersDatabase.registerUser(packet->getUsername(), packet->getPassword(), sender)) {
        sender->write(SignXResponse(usersDatabase.getUserByUsername(packet->getUsername())->getUser().getId(), true).encode());
    } else {
        sender->write(SignXResponse(-1, false).encode());
    }
}

void ChatServer::handleSignIn(EventSocket *sender, SignIn *packet) {
    if (usersDatabase.authenticate(packet->getUsername(), packet->getPassword(), sender)) {
        sender->write(SignXResponse(usersDatabase.getUserByUsername(packet->getUsername())->getUser().getId(), true).encode());
    } else {
        sender->write(SignXResponse(-1, false).encode());
    }
}

void ChatServer::handleSendMessage(EventSocket *sender, MessagePacket *packet) {
    UserEntry *user = usersDatabase.getUserById(packet->getReceiverId());
    if (user) {
        if(user->getSocket())
            user->getSocket()->write(packet->encode());
        else if (sender)
            sender->write(MessagePacket(packet->getSenderId(), packet->getSenderId(), "User is offline").encode());
    }
}

void ChatServer::handleGetUserList(EventSocket *sender, UserList *packet) {
    std::vector<User> users = usersDatabase.getUserList();
    sender->write(UserListResponse(users).encode());
}

ChatServer::ChatServer(EventSocketServer *socketServer) : socketServer(socketServer) {
    socketServer->setReceiver(this);
}

ChatServer::~ChatServer() {
    delete socketServer;
}

void ChatServer::newConnection(EventSocket *socket) {
    std::cout << "new connection" << std::endl;
}

void ChatServer::newMessage(EventSocket *socket) {
    std::cout << "new message" << std::endl;
    Packet *packet = PacketFactory::decode(socket->read());
    if (packet && packet->getHeader() == MessagePacket::headerString){
        handleSendMessage(socket, reinterpret_cast<MessagePacket*>(packet));
    } else if (packet && packet->getHeader() == SignUp::headerString) {
        handleSignUp(socket, reinterpret_cast<SignUp*>(packet));
    } else if (packet && packet->getHeader() == SignIn::headerString) {
        handleSignIn(socket, reinterpret_cast<SignIn*>(packet));
    } else if (packet && packet->getHeader() == SignOut::headerString) {
        //handleSignOut(sender, reinterpret_cast<SignOut*>(packet));
    } else if (packet && packet->getHeader() == UserList::headerString) {
        handleGetUserList(socket, reinterpret_cast<UserList*>(packet));
    }
}

void ChatServer::onDisconnect(EventSocket *socket) {
    std::cout << "disconnected" << std::endl; //TODO: maybe remove user from database???
}
