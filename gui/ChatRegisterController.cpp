//
// Created by Leonardo on 17/08/23.
//

#include "ChatRegisterController.h"
#include "chatview.h"
#include "ChatController.h"

void ChatRegisterController::refresh() {
    chatAPI->refreshUsers();
    std::list<User> userlist = chatAPI->getUsers();
    for (auto user : userlist) {
        model->createChat(user);
    }
}

void ChatRegisterController::openChat(int id, QWidget* parent) {
    auto &chat = model->getChatById(id);
    auto *chatController = new ChatController(&chat, chatAPI); //FIXME: dangling pointer
    auto *chatView = new ChatView(&chat, chatController, parent);
    chatView->show();
}
