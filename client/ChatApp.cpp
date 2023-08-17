//
// Created by Leonardo on 15/08/23.
//

#include "ChatApp.h"

ChatApp::ChatApp(ChatAPI *chatAPI, ChatRegister *chatRegister, QWidget *parent) : chatAPI(chatAPI), chatRegister(chatRegister), QMainWindow(parent) {
    chatRegisterController = new ChatRegisterController(chatRegister, chatAPI); //FIXME: dangling pointer
    chatRegisterView = new ChatRegisterView(chatRegister, chatRegisterController, this);
    setCentralWidget(chatRegisterView);
    setWindowTitle("ChatApp");
    chatAPI->setMediator(this);
}

void ChatApp::notify(Component *sender, const std::string &event) {
    if (sender == chatAPI){
        if (event == "newMessage"){
            chatRegister->addMessage(chatAPI->receiveMessage());
        } else if (event == "signedIn"){
            chatRegister->setCurrentUser(chatAPI->getCurrentUser());
            setWindowTitle("Hello, " + QString::fromStdString(chatRegister->getCurrentUser().getNickname()) + "!");
        } else if (event == "signInFailed"){
            chatRegister->setCurrentUser(User());
            setWindowTitle("ChatApp");
        }
    }
}
