//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_CHATAPI_H
#define CHATPROJ_CHATAPI_H

#include <map>
#include "Mediator.h"
#include "../model/User.h"
#include "../model/Message.h"
#include "../network/ObservableSocket.h"

//TODO: use ObservableSocket to do comunication, MAKE SURE SERVER WORKS FIRST!!

// facade for client side
class ChatAPI : public Component, public Observer {
public:
    ChatAPI();

    bool signUp(const std::string& nickname, const std::string& password);

    bool signIn(const std::string& nickname, const std::string& password);

    bool signOut();

    void sendMessage(const Message& message);

    Message * receiveMessage();

    bool refreshUsers();

    void update() override;

private:
    User currentUser;
    ObservableSocket *socket;
    std::map<int, User> users;


};


#endif //CHATPROJ_CHATAPI_H
