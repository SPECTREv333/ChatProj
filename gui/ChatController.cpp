//
// Created by Leonardo on 17/08/23.
//

#include "ChatController.h"

void ChatController::send(const std::string &message) {
    Message msg(model->getCurrentUser(), model->getRemoteUser(), message);
    chatAPI->sendMessage(msg);
}
