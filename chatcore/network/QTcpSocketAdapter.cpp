//
// Created by Leonardo on 08/07/23.
//

#include <exception>
#include <QTcpSocket>
#include "QTcpSocketAdapter.h"


QTcpSocketAdapter::QTcpSocketAdapter(const std::string& serverAddress, int serverPort, QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &QTcpSocketAdapter::newMessage);
    connect(socket, &QTcpSocket::disconnected, this, &QTcpSocketAdapter::onDisconnect);
    connect(socket, &QTcpSocket::stateChanged, this, &QTcpSocketAdapter::displayState);
    connect(socket, &QAbstractSocket::errorOccurred, this, &QTcpSocketAdapter::displayError);

    socket->connectToHost(QHostAddress(QString::fromStdString(serverAddress)), serverPort);
    if (socket->waitForConnected(3000)){
        qInfo() << "Connection estabilished";
    } else {
        throw std::runtime_error("Connection timed out");
    }
}

void QTcpSocketAdapter::onDisconnect() {
    socket->deleteLater();
    receiver->onDisconnect();
    qInfo() << "QTcpSocketAdapter disconected";
}

void QTcpSocketAdapter::displayState() {
    qInfo() << "socket state changed to " << socket->state();
}

void QTcpSocketAdapter::newMessage(){
    receiver->newMessage();
    qInfo() << "New message";
}

const std::string QTcpSocketAdapter::read() {
    QByteArray buffer;
    buffer = socket->readLine();
    buffer.chop(1);
    std::string messagestr = buffer.toStdString();
    qInfo() << messagestr;
    return messagestr;
}

void QTcpSocketAdapter::write(const std::string &message) {
    socket->write(QString::fromStdString(message).toUtf8());
    socket->write("\n");
    socket->flush();
}

void QTcpSocketAdapter::displayError() {
    qInfo() << socket->errorString();
}

bool QTcpSocketAdapter::isConnected() const {
    return socket->isOpen();
}

const QTcpSocket *QTcpSocketAdapter::getSocket() const {
    return socket;
}

void QTcpSocketAdapter::setSocket(QTcpSocket *socket) {
    this->socket->deleteLater();
    this->socket = socket;
}

QTcpSocketAdapter::QTcpSocketAdapter(QTcpSocket *socket, QObject *parent) {
    this->socket = socket;
}

void QTcpSocketAdapter::setReceiver(EventSocketReceiver *receiver) {
    this->receiver = receiver;
}
