//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_CHAT_H
#define CHATPROJ_CHAT_H

#include <list>
#include "Subject.h"
#include "Message.h"

class Chat : public Subject {
public:
    Chat(const User& currentUser, const User& remoteUser) : currentUser(currentUser), remoteUser(remoteUser) {};

    Chat(const Chat &rhs) = delete;

    Chat &operator=(const Chat &rhs) = delete;

    void addMessage(Message &message);

    void addObserver(Observer *o) override;

    void removeObserver(Observer *o) override;

    void notify() override;

    const std::list<Message *> &getMessages() const;

    const User &getCurrentUser() const;

    const User &getRemoteUser() const;

private:
    std::list<Observer *> observers;
    User currentUser;
    User remoteUser;
    std::list<Message *> messages;
};


#endif //CHATPROJ_CHAT_H
