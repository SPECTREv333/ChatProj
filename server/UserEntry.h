//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_USERENTRY_H
#define CHATPROJ_USERENTRY_H


#include "../model/User.h"
#include "../network/ObservableSocket.h"

class UserEntry {
public:
    UserEntry(const User &user, const std::string &password, ObservableSocket *socket);

    const User &getUser() const;

    void setUser(const User &user);

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    ObservableSocket *getSocket() const;

    void setSocket(ObservableSocket *socket);

private:
    User user;
    std::string password;
    ObservableSocket *socket;

};


#endif //CHATPROJ_USERENTRY_H
