//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_USER_H
#define CHATPROJ_USER_H

#include <string>
#include <utility>

class User {
public:
    User() = default;

    explicit User(int id, const std::string& nickname) : id(id), nickname(nickname) {};

    User(const User& rhs) {
        id = rhs.id;
        nickname = std::string(rhs.nickname);
    }

    User& operator=(const User& rhs) {
        id = rhs.id;
        nickname = std::string(rhs.nickname);
        return *this;
    }

    bool operator==(const User &rhs) const;

    bool operator!=(const User &rhs) const;

    int getId() const;

    void setId(int id);

    const std::string &getNickname() const;

    void setNickname(const std::string &nickname);

private:
    int id;
    std::string nickname;
};


#endif //CHATPROJ_USER_H
