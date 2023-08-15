//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_CHATSERVER_H
#define CHATPROJ_CHATSERVER_H

#include "UsersDatabase.h"
#include "../network/EventSocketServer.h"
#include "concrete_packets/SignUp.h"
#include "concrete_packets/SignIn.h"
#include "concrete_packets/SignOut.h"
#include "concrete_packets/MessagePacket.h"
#include "concrete_packets/UserList.h"
#include "../network/SocketServer.h"

class ChatServer : public EventSocketServer {
public:
    explicit ChatServer(int port);

    ~ChatServer() override;

    void notify(Component *sender, const std::string &event) override;

    void notify(ObservableSocket *sender, const std::string &event) override;

private:
    void handleSignUp(ObservableSocket *sender, SignUp *packet);
    void handleSignIn(ObservableSocket *sender, SignIn *packet);
    //void handleSignOut(ObservableSocket *sender, SignOut *packet); //TODO: implement
    void handleSendMessage(ObservableSocket *sender, MessagePacket *packet);
    void handleGetUserList(ObservableSocket *sender, UserList *packet);

    SocketServer* socketServer;
    UsersDatabase usersDatabase;

};


#endif //CHATPROJ_CHATSERVER_H
