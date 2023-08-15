//
// Created by Leonardo on 15/08/23.
//

#include "UsersDatabase.h"

bool UsersDatabase::authenticate(const std::string &username, const std::string &password, ObservableSocket *socket) {
    auto it = usernameMap.find(username);
    if (it != usernameMap.end() && it->second->getPassword() == password) {
        it->second->setSocket(socket);
        return true;
    }
    return false;
}

bool UsersDatabase::registerUser(const std::string &username, const std::string &password, ObservableSocket *socket) {
    auto it = usernameMap.find(username);
    if (it == usernameMap.end()) {
        User user(idCounter++, username);
        users.emplace_back(user, password, socket);
        usernameMap.insert(std::pair<std::string, UserEntry *>(username, &users.back()));
        idMap.insert(std::pair<int, UserEntry *>(idCounter++, &users.back()));
        return true;
    }
    return false;
}

UserEntry *UsersDatabase::getUserById(int id) {
    auto it = idMap.find(id);
    if (it != idMap.end())
        return it->second;
    return nullptr;
}

UserEntry *UsersDatabase::getUserByUsername(const std::string &username) {
    auto it = usernameMap.find(username);
    if (it != usernameMap.end())
        return it->second;
    return nullptr;
}

std::vector<User> UsersDatabase::getUserList() const {
    std::vector<User> userList;
    for (auto it = users.begin(); it != users.end(); ++it) {
        userList.push_back(it->getUser());
    }
    return userList;
}


