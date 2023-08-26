//
// Created by Leonardo on 17/08/23.
//

#ifndef CHATPROJ_CHATREGISTERCONTROLLER_H
#define CHATPROJ_CHATREGISTERCONTROLLER_H

#include <QWidget>
#include "../model/ChatRegister.h"
#include "Mediator.h"
#include "../client_api/ChatAPI.h"
#include "ChatController.h"

class ChatRegisterController {
public:
    ChatRegisterController(ChatRegister *model, ChatAPI *chatApi) :
            model(model),
            chatAPI(chatApi) {};

    ~ChatRegisterController();

    void refresh();

    void openChat(int id, QWidget *parent = nullptr);

private:
    ChatAPI *chatAPI;
    ChatRegister *model;
    std::list<ChatController*> managedChatControllers;
};


#endif //CHATPROJ_CHATREGISTERCONTROLLER_H
