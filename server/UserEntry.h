//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_USERENTRY_H
#define CHATPROJ_USERENTRY_H


#include "../model/User.h"
#include "../network/EventSocket.h"

class UserEntry {
public:
    UserEntry(const User &user, const std::string &password, EventSocket *socket);

    const User &getUser() const;

    void setUser(const User &user);

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    EventSocket *getSocket() const;

    void setSocket(EventSocket *socket);

private:
    User user;
    std::string password;
    EventSocket *socket;

};


#endif //CHATPROJ_USERENTRY_H
