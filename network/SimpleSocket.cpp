//
// Created by Leonardo on 13/08/23.
//

#include "SimpleSocket.h"

SimpleSocket::SimpleSocket() {
    socket = new Socket("127.0.0.1", 6666); //TODO: make this configurable
    socket->addObserver(this);
}

std::string SimpleSocket::read() {
    return socket->read();
}

void SimpleSocket::write(const std::string &text) {
    socket->write(text);
}

void SimpleSocket::notify() {
    for (auto &observer: observers)
        observer->update();
}

void SimpleSocket::addObserver(Observer *o) {
    observers.push_back(o);
}

void SimpleSocket::removeObserver(Observer *o) {
    observers.remove(o);
}

void SimpleSocket::update() {
    notify();
}

std::string SimpleSocket::syncread() {
    return socket->syncread();
}

SimpleSocket::SimpleSocket(Socket *socket) {
    this->socket = socket;
    socket->addObserver(this);
}

SimpleSocket::~SimpleSocket() {
    delete socket;
}
