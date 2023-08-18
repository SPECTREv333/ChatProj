//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_CHATREGISTER_H
#define CHATPROJ_CHATREGISTER_H

#include <map>
#include "Chat.h"

class ChatRegister : public Subject {
public:
    explicit ChatRegister() = default;

    explicit ChatRegister(const User& currentUser) : currentUser(currentUser) {};

    ~ChatRegister() override;

    void createChat(const User &remoteUser);

    void addMessage(Message *message);

    Chat &getChat(const User &remote) const;

    Chat &getChatById(int id) const;

    void addObserver(Observer *o) override;

    void removeObserver(Observer *o) override;

    void notify() override;

    const User &getCurrentUser() const;

    void setCurrentUser(const User &currentUser);

    const std::list<Chat *> getChats() const;

private:
    User currentUser;
    std::list<Observer *> observers;
    std::map<int, Chat*> chats;
};


#endif //CHATPROJ_CHATREGISTER_H
