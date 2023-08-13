//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_CHATAPI_H
#define CHATPROJ_CHATAPI_H

#include "Mediator.h"
#include "../model/User.h"
#include "../model/Message.h"

//TODO: use ObservableSocket to do comunication, MAKE SURE SERVER WORKS FIRST!!

class ChatAPI : public Component {
public:
    ChatAPI() = default;

    bool signUp(const std::string& nickname, const std::string& password);

    bool signIn(const std::string& nickname, const std::string& password);

    bool signOut();

    bool sendMessage(const Message& message);

    Message receiveMessage();

private:
    User currentUser;

};


#endif //CHATPROJ_CHATAPI_H
