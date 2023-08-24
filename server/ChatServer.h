//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_CHATSERVER_H
#define CHATPROJ_CHATSERVER_H

#include "UsersDatabase.h"
#include "EventSocketServerReceiver.h"
#include "concrete_packets/SignUp.h"
#include "concrete_packets/SignIn.h"
#include "concrete_packets/SignOut.h"
#include "concrete_packets/MessagePacket.h"
#include "concrete_packets/UserList.h"
#include "QTcpServerAdapter.h"

class ChatServer : public EventSocketServerReceiver {
public:
    explicit ChatServer(EventSocketServer *socketServer);

    ~ChatServer() override;

    void newConnection(EventSocket *socket) override;

    void newMessage(EventSocket *socket) override;

    void onDisconnect(EventSocket *socket) override;

private:
    void handleSignUp(EventSocket *sender, SignUp *packet);
    void handleSignIn(EventSocket *sender, SignIn *packet);
    //void handleSignOut(EventSocket *sender, SignOut *packet); //TODO: implement
    void handleSendMessage(EventSocket *sender, MessagePacket *packet);
    void handleGetUserList(EventSocket *sender, UserList *packet);

    EventSocketServer* socketServer;
    UsersDatabase usersDatabase;

};


#endif //CHATPROJ_CHATSERVER_H
