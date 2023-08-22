//
// Created by Leonardo on 22/08/23.
//

#ifndef CHATPROJ_EVENTSOCKETSERVER_H
#define CHATPROJ_EVENTSOCKETSERVER_H

#include "Mediator.h"
#include "EventSocketReceiver.h"

class EventSocketServer : public Component {
public:
    virtual ~EventSocketServer() = default;

    virtual void setMediator(EventSocketReceiver *mediator) = 0;

};


#endif //CHATPROJ_EVENTSOCKETSERVER_H
