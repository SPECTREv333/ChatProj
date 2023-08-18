//
// Created by Leonardo on 15/08/23.
//

#include "ChatRegister.h"

void ChatRegister::createChat(const User &remoteUser) {
    Chat* chat = new Chat(currentUser, remoteUser);
    chats.insert(std::make_pair(remoteUser.getId(), chat));
    notify();
}

void ChatRegister::addMessage(Message &message) {
    auto chat = chats.find(message.getSender().getId());
    if (chat != chats.end()) {
        chat->second->addMessage(message);
    }
}

ChatRegister::~ChatRegister() {
    for (auto &chat: chats) {
        delete chat.second;
    }
}

Chat &ChatRegister::getChat(const User &remote) const {
    return *chats.at(remote.getId());
}

void ChatRegister::addObserver(Observer *o) {
    observers.push_back(o);
}

void ChatRegister::removeObserver(Observer *o) {
    observers.remove(o);
}

void ChatRegister::notify() {
    for (auto &observer: observers)
        observer->update();
}

const User &ChatRegister::getCurrentUser() const {
    return currentUser;
}

void ChatRegister::setCurrentUser(const User &currentUser) {
    ChatRegister::currentUser = currentUser;
    notify();
}

const std::list<Chat *> ChatRegister::getChats() const {
    std::list<Chat*> chatList;
    for (auto &chat: chats) {
        chatList.push_back(chat.second);
    }
    return chatList;
}

Chat &ChatRegister::getChatById(int id) const {
    return *chats.at(id);
}


