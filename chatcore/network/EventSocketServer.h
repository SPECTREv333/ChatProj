//
// Created by Leonardo on 22/08/23.
//

#ifndef CHATPROJ_EVENTSOCKETSERVER_H
#define CHATPROJ_EVENTSOCKETSERVER_H

#include "Mediator.h"
#include "EventSocketServerReceiver.h"

class EventSocketServer {
public:
    virtual ~EventSocketServer() = default;

    virtual void setReceiver(EventSocketServerReceiver *receiver) = 0;

};


#endif //CHATPROJ_EVENTSOCKETSERVER_H
