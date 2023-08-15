//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_EVENTSOCKETSERVER_H
#define CHATPROJ_EVENTSOCKETSERVER_H

#include "Mediator.h"
#include "ObservableSocket.h"

class EventSocketServer : public Mediator {
public:
    virtual ~EventSocketServer() = default;

    void notify(Component *sender, const std::string &event) override = 0;

    virtual void notify(ObservableSocket *sender, const std::string &event) = 0;

};


#endif //CHATPROJ_EVENTSOCKETSERVER_H
