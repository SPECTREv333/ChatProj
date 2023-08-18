//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_SIMPLESOCKET_H
#define CHATPROJ_SIMPLESOCKET_H

// SimpleSocket uses a QtTcpSocket wrapper to handle the socket
// as it inherits from ObservableSocket it is a Subject
// when its readable it notifies its observers
// it cant be a QObject as it already inherits from ObservableSocket (MOC error)

//TODO: finish simple socket

#include "Socket.h"
#include "ObservableSocket.h"

class SimpleSocket : public ObservableSocket, public Observer {
public:
    SimpleSocket(const std::string& address, int port);

    explicit SimpleSocket(Socket *socket);

    ~SimpleSocket() override;

    std::string read() override;

    std::string syncread() override;

    void write(const std::string &text) override;

    void notify() override;

    void update() override;

    void addObserver(Observer *o) override;

    void removeObserver(Observer *o) override;

private:
    Socket *socket;
    std::list<Observer *> observers;
};


#endif //CHATPROJ_SIMPLESOCKET_H
