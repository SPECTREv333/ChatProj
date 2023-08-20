//
// Created by Leonardo on 15/08/23.
//

#include "SocketServer.h"
#include "Socket.h"

void SocketServer::newConnection() {
    while (server->hasPendingConnections()) {
        QTcpSocket* socket = server->nextPendingConnection();
        addConnection(socket);
    }
}

void SocketServer::onDisconnect() {
    auto *socket = reinterpret_cast<QTcpSocket *>(sender());
    eventSocketServer->notify(this, "disconnected");
    clients.remove(socket);
}

void SocketServer::newMessage() {
    auto *socket = reinterpret_cast<QTcpSocket *>(sender());
    eventSocketServer->notify(clients[socket], "newMessage");
}

void SocketServer::addConnection(QTcpSocket *socket) {
    ObservableSocket* connection = new Socket(socket);

    clients.insert(socket, connection);

    connect(socket, &QTcpSocket::readyRead, this, &SocketServer::newMessage);
    connect(socket, &QTcpSocket::disconnected, this, &SocketServer::onDisconnect);

    eventSocketServer->notify(connection, "newConnection");
}

SocketServer::SocketServer(int port, EventSocketServer *mediator) {
    server = new QTcpServer(this);
    eventSocketServer = mediator;

    if (server->listen(QHostAddress::Any, port)) {
        connect(server, &QTcpServer::newConnection, this, &SocketServer::newConnection);
    }
}




