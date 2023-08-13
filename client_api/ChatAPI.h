//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_CHATAPI_H
#define CHATPROJ_CHATAPI_H

#include "Mediator.h"
#include "../model/User.h"

class ChatAPI : public Component {
public:
    ChatAPI() = default;

    bool signUp(const std::string& nickname, const std::string& password);

    bool signIn(const std::string& nickname, const std::string& password);

    bool signOut();

    bool sendMessage(const std::string& message);

    

private:
    User currentUser;



};


#endif //CHATPROJ_CHATAPI_H
