//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_MEDIATOR_H
#define CHATPROJ_MEDIATOR_H

#include <string>

class Component;

class Mediator {
public:
    virtual void notify(Component *sender, const std::string &event) = 0;
};

class Component {
protected:
    Mediator *mediator;
public:
    explicit Component() {
        mediator = nullptr;
    };

    explicit Component(Mediator *mediator) : mediator(mediator) {}

    virtual ~Component() = default;

    void setMediator(Mediator *mediator) {
        this->mediator = mediator;
    }
};


#endif //CHATPROJ_MEDIATOR_H
