//
// Created by Leonardo on 15/08/23.
//

#include "ChatApp.h"

ChatApp::ChatApp(ChatAPI *chatAPI, ChatRegister *chatRegister) : chatAPI(chatAPI), chatRegister(chatRegister) {
    chatRegisterController = new ChatRegisterController(chatRegister, chatAPI); //FIXME: dangling pointer
    chatRegisterView = new ChatRegisterView(chatRegister, chatRegisterController, this);
    chatRegisterView->show();
}
