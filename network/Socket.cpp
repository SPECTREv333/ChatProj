//
// Created by Leonardo on 08/07/23.
//

#include <exception>
#include <QTcpSocket>
#include "Socket.h"


Socket::Socket(const std::string& serverAddress, int serverPort, QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &Socket::newMessage);
    connect(socket, &QTcpSocket::disconnected, this, &Socket::onDisconnect);
    connect(socket, &QTcpSocket::stateChanged, this, &Socket::displayState);
    connect(socket, &QAbstractSocket::errorOccurred, this, &Socket::displayError);

    socket->connectToHost(QHostAddress(QString::fromStdString(serverAddress)), serverPort);
    if (socket->waitForConnected(3000)){
        qInfo() << "Connection estabilished";
    } else {
        throw std::runtime_error("Connection timed out");
    }
}

void Socket::onDisconnect() {
    socket->deleteLater();
    socket = nullptr;
    qInfo() << "Socket disconected";
}

Socket::~Socket() {
    if(socket && socket->isOpen()){
        socket->close();
    }
}

void Socket::displayState() {
    qInfo() << "socket state changed to " << socket->state();
}

void Socket::newMessage(){
    qInfo() << "New message";
    notify();
}

const std::string Socket::read() {
    QByteArray buffer;
    buffer = socket->readAll();
    std::string messagestr = buffer.toStdString();
    qInfo() << messagestr;
    return messagestr;
}

bool Socket::write(const std::string &message) {
    if (!socket || !socket->isOpen()){
        return false;
    }
    socket->write(QString::fromStdString(message).toUtf8());
    socket->flush();
    return true;
}

void Socket::displayError() {
    qInfo() << socket->errorString();
}

const std::string Socket::syncread() {
    QByteArray buffer;
    socket->waitForReadyRead();
    buffer = socket->readAll();
    std::string messagestr = buffer.toStdString();
    qInfo() << messagestr;
    return messagestr;
}

const bool Socket::isConnected() const {
    return socket->isOpen();
}

void Socket::addObserver(Observer *observer) {
    observers.push_back(observer);
}

void Socket::removeObserver(Observer *observer) {
    observers.remove(observer);
}

void Socket::notify() {
    for (auto observer : observers) {
        observer->update();
    }
}

const QTcpSocket *Socket::getSocket() const {
    return socket;
}

void Socket::setSocket(QTcpSocket *socket) {
    this->socket->deleteLater();
    this->socket = socket;
}

Socket::Socket(QTcpSocket *socket, QObject *parent) {
    this->socket = socket;
}
