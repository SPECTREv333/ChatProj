//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_MESSAGE_H
#define CHATPROJ_MESSAGE_H

#include "User.h"

class Message {
public:
    Message(const User& sender, const User& receiver, const std::string& content) : sender(sender), receiver(receiver),
                                                                                    content(content) {};

    const User &getSender() const {
        return sender;
    }

    const User &getReceiver() const {
        return receiver;
    }

    const std::string &getContent() const {
        return content;
    }

    void setContent(const std::string &content) {
        Message::content = content;
    }

private:
    const User& sender;
    const User& receiver;
    std::string content;
};




#endif //CHATPROJ_MESSAGE_H
