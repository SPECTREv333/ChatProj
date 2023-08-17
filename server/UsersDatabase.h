//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_USERSDATABASE_H
#define CHATPROJ_USERSDATABASE_H

#include <vector>
#include <map>
#include "UserEntry.h"

class UsersDatabase {
public:
    UsersDatabase() = default;

    bool authenticate(const std::string &username, const std::string &password, ObservableSocket *socket);

    bool registerUser(const std::string &username, const std::string &password, ObservableSocket *socket);

    UserEntry* getUserById(int id);

    UserEntry* getUserByUsername(const std::string& username);

    std::vector<User> getUserList() const;

private:
    int idCounter = 0;
    std::vector<UserEntry*> users;
    std::map<std::string, UserEntry*> usernameMap;
    std::map<int, UserEntry*> idMap;

};


#endif //CHATPROJ_USERSDATABASE_H
