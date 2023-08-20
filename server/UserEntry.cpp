//
// Created by Leonardo on 15/08/23.
//

#include "UserEntry.h"

UserEntry::UserEntry(const User &user, const std::string &password, EventSocket *socket) : user(user),
                                                                                           password(password),
                                                                                           socket(socket) {}

const User &UserEntry::getUser() const {
    return user;
}

void UserEntry::setUser(const User &user) {
    UserEntry::user = user;
}

const std::string &UserEntry::getPassword() const {
    return password;
}

void UserEntry::setPassword(const std::string &password) {
    UserEntry::password = password;
}

EventSocket *UserEntry::getSocket() const {
    return socket;
}

void UserEntry::setSocket(EventSocket *socket) {
    if (this->socket != nullptr)
        delete this->socket;
    UserEntry::socket = socket;
}
