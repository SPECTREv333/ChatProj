//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_OBSERVABLESOCKET_H
#define CHATPROJ_OBSERVABLESOCKET_H

#include "Subject.h"
#include <string>

// abstract class ObservableSocket
// has only 2 pure virtual methods read and write
// it is a Subject, when its readable it notifies its observers
class ObservableSocket : public Subject {
public:
    virtual ~ObservableSocket() = default;
    virtual std::string read() = 0;
    virtual void write(const std::string &text) = 0;
    virtual std::string syncread() = 0;
};


#endif //CHATPROJ_OBSERVABLESOCKET_H
