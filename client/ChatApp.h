//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_CHATAPP_H
#define CHATPROJ_CHATAPP_H

#include <QMainWindow>
#include "Mediator.h"
#include "../client_api/ChatAPI.h"
#include "../model/ChatRegister.h"
#include "../gui/ChatRegisterController.h"
#include "../gui/chatregisterview.h"

class ChatApp : public QMainWindow {
Q_OBJECT
public:
    ChatApp(ChatAPI *chatAPI, ChatRegister *chatRegister);

private:
    ChatAPI *chatAPI;
    ChatRegister *chatRegister;
    ChatRegisterController *chatRegisterController;
    ChatRegisterView *chatRegisterView;

};


#endif //CHATPROJ_CHATAPP_H
