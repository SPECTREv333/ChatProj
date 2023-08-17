//
// Created by Leonardo on 17/08/23.
//

#ifndef CHATPROJ_CHATCONTROLLER_H
#define CHATPROJ_CHATCONTROLLER_H


#include "../model/Chat.h"
#include "../client_api/ChatAPI.h"

class ChatController {

public:
    ChatController(Chat *model, ChatAPI *chatApi) :
            model(model),
            chatAPI(chatApi) {};

    void send(const std::string &message);

private:
    ChatAPI *chatAPI;
    Chat *model;

};


#endif //CHATPROJ_CHATCONTROLLER_H
