//
// Created by Leonardo on 15/08/23.
//

#include <iostream>
#include "ChatServer.h"
#include "../protocol/PacketFactory.h"
#include "concrete_packets/SignXResponse.h"
#include "concrete_packets/UserListResponse.h"

void ChatServer::notify(Component *sender, const std::string &event) {
    return; // TODO: handle disconnect
}

void ChatServer::notify(ObservableSocket *sender, const std::string &event) {
    if (event == "newConnection") {
        std::cout << "new connection" << std::endl;
    } else if (event == "newMessage") {
        std::cout << "new message" << std::endl;
        Packet *packet = PacketFactory::decode(sender->read());
        if (packet && packet->getHeader() == MessagePacket::headerString){
            handleSendMessage(sender, reinterpret_cast<MessagePacket*>(packet));
        } else if (packet && packet->getHeader() == SignUp::headerString) {
            handleSignUp(sender, reinterpret_cast<SignUp*>(packet));
        } else if (packet && packet->getHeader() == SignIn::headerString) {
            handleSignIn(sender, reinterpret_cast<SignIn*>(packet));
        } else if (packet && packet->getHeader() == SignOut::headerString) {
            //handleSignOut(sender, reinterpret_cast<SignOut*>(packet));
        } else if (packet && packet->getHeader() == UserList::headerString) {
            handleGetUserList(sender, reinterpret_cast<UserList*>(packet));
        }
    }
}

void ChatServer::handleSignUp(ObservableSocket *sender, SignUp *packet) {
    if (usersDatabase.registerUser(packet->getUsername(), packet->getPassword(), sender)) {
        sender->write(SignXResponse(usersDatabase.getUserByUsername(packet->getUsername())->getUser().getId(), true).encode());
    } else {
        sender->write(SignXResponse(-1, false).encode());
    }
}

void ChatServer::handleSignIn(ObservableSocket *sender, SignIn *packet) {
    if (usersDatabase.authenticate(packet->getUsername(), packet->getPassword(), sender)) {
        sender->write(SignXResponse(usersDatabase.getUserByUsername(packet->getUsername())->getUser().getId(), true).encode());
    } else {
        sender->write(SignXResponse(-1, false).encode());
    }
}

void ChatServer::handleSendMessage(ObservableSocket *sender, MessagePacket *packet) {
    UserEntry *user = usersDatabase.getUserById(packet->getReceiverId());
    if (user) {
        if(user->getSocket())
            user->getSocket()->write(packet->encode());
        else if (sender)
            sender->write(MessagePacket(packet->getSenderId(), packet->getSenderId(), "User is offline").encode());
    }
}

void ChatServer::handleGetUserList(ObservableSocket *sender, UserList *packet) {
    std::vector<User> users = usersDatabase.getUserList();
    sender->write(UserListResponse(users).encode());
}

ChatServer::ChatServer(int port) {
    socketServer = new SocketServer(port, this);
}

ChatServer::~ChatServer() {
    delete socketServer;
}
