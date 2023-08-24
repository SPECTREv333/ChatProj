//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_CHATSERVER_H
#define CHATPROJ_CHATSERVER_H

#include "UsersDatabase.h"
#include "../network/EventSocketReceiver.h"
#include "concrete_packets/SignUp.h"
#include "concrete_packets/SignIn.h"
#include "concrete_packets/SignOut.h"
#include "concrete_packets/MessagePacket.h"
#include "concrete_packets/UserList.h"
#include "../network/QTcpServerAdapter.h"

class ChatServer : public EventSocketReceiver {
public:
    explicit ChatServer(int port);

    ~ChatServer() override;

    void notify(Component *sender, const std::string &event) override;

    void notify(EventSocket *sender, const std::string &event) override;

private:
    void handleSignUp(EventSocket *sender, SignUp *packet);
    void handleSignIn(EventSocket *sender, SignIn *packet);
    //void handleSignOut(EventSocket *sender, SignOut *packet); //TODO: implement
    void handleSendMessage(EventSocket *sender, MessagePacket *packet);
    void handleGetUserList(EventSocket *sender, UserList *packet);

    QTcpServerAdapter* socketServer;
    UsersDatabase usersDatabase;

};


#endif //CHATPROJ_CHATSERVER_H
