//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATCLIENT_OBSERVER_H
#define CHATCLIENT_OBSERVER_H


class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};


#endif //CHATCLIENT_OBSERVER_H
