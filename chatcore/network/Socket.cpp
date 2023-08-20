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
    mediator->notify(this, "disconnect");
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
    mediator->notify(this, "message");
    qInfo() << "New message";
}

const std::string Socket::read() {
    QByteArray buffer;
    buffer = socket->readLine();
    buffer.chop(1);
    std::string messagestr = buffer.toStdString();
    qInfo() << messagestr;
    return messagestr;
}

void Socket::write(const std::string &message) {
    socket->write(QString::fromStdString(message).toUtf8());
    socket->write("\n");
    socket->flush();
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

bool Socket::isConnected() const {
    return socket->isOpen();
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
