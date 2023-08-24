//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_EVENTSOCKETSERVERRECEIVER_H
#define CHATPROJ_EVENTSOCKETSERVERRECEIVER_H

#include "Mediator.h"
#include "EventSocket.h"

class EventSocketServerReceiver {
public:
    virtual ~EventSocketServerReceiver() = default;

    virtual void newConnection(EventSocket *socket) = 0;

    virtual void newMessage(EventSocket *socket) = 0;

    virtual void onDisconnect(EventSocket *socket) = 0;

};


#endif //CHATPROJ_EVENTSOCKETSERVERRECEIVER_H
