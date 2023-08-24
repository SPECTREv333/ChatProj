//
// Created by Leonardo on 24/08/23.
//

#ifndef CHATPROJ_EVENTSOCKETRECEIVER_H
#define CHATPROJ_EVENTSOCKETRECEIVER_H

class EventSocketReceiver {
public:
    virtual ~EventSocketReceiver() = default;

    virtual void newMessage() = 0;

    virtual void onDisconnect() = 0;
};


#endif //CHATPROJ_EVENTSOCKETRECEIVER_H
