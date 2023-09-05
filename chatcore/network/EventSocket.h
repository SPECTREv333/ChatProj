//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_EVENTSOCKET_H
#define CHATPROJ_EVENTSOCKET_H

#include "Mediator.h"
#include "EventSocketReceiver.h"
#include <string>

// abstract class EventSocket
// has only 2 pure virtual methods read and write
// it is a Subject, when its readable it notifies its observers
class EventSocket {
public:
    virtual ~EventSocket() = default;
    virtual const std::string read() = 0;
    virtual void write(const std::string &text) = 0;
    virtual void setReceiver(EventSocketReceiver *receiver) = 0;
};


#endif //CHATPROJ_EVENTSOCKET_H
