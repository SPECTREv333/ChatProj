//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_EVENTSOCKETRECEIVER_H
#define CHATPROJ_EVENTSOCKETRECEIVER_H

#include "Mediator.h"
#include "EventSocket.h"

class EventSocketReceiver : public Mediator {
public:
    virtual ~EventSocketReceiver() = default;

    void notify(Component *sender, const std::string &event) override = 0;

    virtual void notify(EventSocket *sender, const std::string &event) = 0;

};


#endif //CHATPROJ_EVENTSOCKETRECEIVER_H
