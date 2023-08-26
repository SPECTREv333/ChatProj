//
// Created by Leonardo on 15/08/23.
//

#include "Chat.h"

void Chat::addMessage(Message &message) {
    auto* msg = new Message(message);
    messages.push_back(msg);
    notify();
}

void Chat::addObserver(Observer *o) {
    observers.push_back(o);
}

void Chat::removeObserver(Observer *o) {
    observers.remove(o);
}

void Chat::notify() {
    for (auto &observer: observers)
        observer->update();
}

const User &Chat::getCurrentUser() const {
    return currentUser;
}

const User &Chat::getRemoteUser() const {
    return remoteUser;
}

const std::list<Message *> &Chat::getMessages() const {
    return messages;
}

Chat::~Chat() {//delete all messages
    for (auto &message: messages)
        delete message;
}
