//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_CHATSERVER_H
#define CHATPROJ_CHATSERVER_H


#include "../network/EventSocketServer.h"

class ChatServer : public EventSocketServer {
public:
    ChatServer() = default;

    void notify(Component *sender, const std::string &event) override;

    void notify(ObservableSocket *sender, const std::string &event) override;

private:


};


#endif //CHATPROJ_CHATSERVER_H
