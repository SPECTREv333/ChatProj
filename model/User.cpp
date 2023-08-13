//
// Created by Leonardo on 13/08/23.
//

#include "User.h"

const std::string &User::getNickname() const {
    return nickname;
}

void User::setNickname(const std::string &nickname) {
    User::nickname = nickname;
}

bool User::operator==(const User &rhs) const {
    return id == rhs.id;
}

bool User::operator!=(const User &rhs) const {
    return !(rhs == *this);
}

int User::getId() const {
    return id;
}

void User::setId(int id) {
    User::id = id;
}
