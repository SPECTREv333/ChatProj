//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATCLIENT_SUBJECT_H
#define CHATCLIENT_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject() = default;
    virtual void notify() = 0;
    virtual void addObserver(Observer *o) = 0;
    virtual void removeObserver(Observer *o) = 0;
};


#endif //CHATCLIENT_SUBJECT_H
