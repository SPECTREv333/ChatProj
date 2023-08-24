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

void QTcpServerAdapter::onDisconnect() {
    auto *socket = reinterpret_cast<QTcpSocket *>(sender());
    if (eventSocketServer) eventSocketServer->notify(this, "disconnected");
    clients.remove(socket);
}

void QTcpServerAdapter::newMessage() {
    auto *socket = reinterpret_cast<QTcpSocket *>(sender());
    if (eventSocketServer) eventSocketServer->notify(clients[socket], "newMessage");
}

void QTcpServerAdapter::addConnection(QTcpSocket *socket) {
    EventSocket* connection = new QTcpSocketAdapter(socket);

    clients.insert(socket, connection);

    connect(socket, &QTcpSocket::readyRead, this, &QTcpServerAdapter::newMessage);
    connect(socket, &QTcpSocket::disconnected, this, &QTcpServerAdapter::onDisconnect);

    if (eventSocketServer) eventSocketServer->notify(connection, "newConnection");
}

QTcpServerAdapter::QTcpServerAdapter(int port, EventSocketReceiver *mediator) {
    server = new QTcpServer(this);
    eventSocketServer = mediator;

    if (server->listen(QHostAddress::Any, port)) {
        connect(server, &QTcpServer::newConnection, this, &QTcpServerAdapter::newConnection);
    }
}

void QTcpServerAdapter::setMediator(EventSocketReceiver *mediator) {
    eventSocketServer = mediator;
}








