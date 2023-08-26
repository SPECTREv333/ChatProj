//
// Created by Leonardo on 15/08/23.
//

#include "QTcpServerAdapter.h"
#include "QTcpSocketAdapter.h"

void QTcpServerAdapter::newConnection() {
    while (server->hasPendingConnections()) {
        QTcpSocket* socket = server->nextPendingConnection();
        addConnection(socket);
    }
}

// when the disconnect signal is emitted, the associated EventSocket
// destructor is called, which in turn deletes the socket
// QTcpServerAdapter does not have ownership of the socket, it's just a mere address
// this might need to be changed to a weak pointer
void QTcpServerAdapter::onDisconnect() {
    auto *socket = reinterpret_cast<QTcpSocket *>(sender());
    if (receiver) receiver->onDisconnect(clients[socket]);
    clients.remove(socket);
}

void QTcpServerAdapter::newMessage() {
    auto *socket = reinterpret_cast<QTcpSocket *>(sender());
    if (receiver) receiver->newMessage(clients[socket]);
}

void QTcpServerAdapter::addConnection(QTcpSocket *socket) {
    EventSocket* connection = new QTcpSocketAdapter(socket);

    clients.insert(socket, connection);

    connect(socket, &QTcpSocket::readyRead, this, &QTcpServerAdapter::newMessage);
    connect(socket, &QTcpSocket::disconnected, this, &QTcpServerAdapter::onDisconnect);

    if (receiver) receiver->newConnection(connection);
}

QTcpServerAdapter::QTcpServerAdapter(int port, EventSocketServerReceiver *receiver) {
    server = new QTcpServer(this);
    this->receiver = receiver;

    if (server->listen(QHostAddress::Any, port)) {
        connect(server, &QTcpServer::newConnection, this, &QTcpServerAdapter::newConnection);
    }
}

void QTcpServerAdapter::setReceiver(EventSocketServerReceiver *receiver) {
    this->receiver = receiver;
}
