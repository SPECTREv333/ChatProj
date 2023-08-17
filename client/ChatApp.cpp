//
// Created by Leonardo on 15/08/23.
//

#include "ChatApp.h"

ChatApp::ChatApp(ChatAPI *chatAPI, ChatRegister *chatRegister, QWidget *parent) : chatAPI(chatAPI), chatRegister(chatRegister), QMainWindow(parent) {
    chatRegisterController = new ChatRegisterController(chatRegister, chatAPI); //FIXME: dangling pointer
    chatRegisterView = new ChatRegisterView(chatRegister, chatRegisterController, this);
    setCentralWidget(chatRegisterView);
    setWindowTitle("Hello, " + QString::fromStdString(chatRegister->getCurrentUser().getNickname()) + "!");
    chatAPI->setMediator(this);
}

void ChatApp::notify(Component *sender, const std::string &event) {
    if (sender == chatAPI){
        if (event == "newmessage"){
            chatRegister->addMessage(chatAPI->receiveMessage());
        }
    }
}
