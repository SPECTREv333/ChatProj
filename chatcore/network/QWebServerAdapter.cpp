//
// Created by leonardo on 05/09/23.
//

#include <QFile>
#include <QSslKey>
#include "QWebServerAdapter.h"
#include "QWebSocketAdapter.h"

QWebServerAdapter::QWebServerAdapter(int port, EventSocketServerReceiver *mediator) {
    server = new QWebSocketServer("ChatServer", QWebSocketServer::SecureMode, this);
    this->receiver = mediator;

    QSslConfiguration sslConfiguration;
    QFile certFile(QStringLiteral("cert.pem"));
    QFile keyFile(QStringLiteral("key.pem"));
    certFile.open(QIODevice::ReadOnly);
    keyFile.open(QIODevice::ReadOnly);
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setLocalCertificate(QSslCertificate(&certFile));
    sslConfiguration.setPrivateKey(QSslKey(&keyFile, QSsl::Rsa));
    certFile.close();
    keyFile.close();
    server->setSslConfiguration(sslConfiguration);

    if (server->listen(QHostAddress::Any, port)) {
        connect(server, &QWebSocketServer::newConnection, this, &QWebServerAdapter::newConnection);
        connect(server, &QWebSocketServer::sslErrors, this, &QWebServerAdapter::onSslError);
    }
}

void QWebServerAdapter::newConnection() {
    QWebSocket* socket = server->nextPendingConnection();
    addConnection(socket);
}

void QWebServerAdapter::addConnection(QWebSocket *socket) {
    EventSocket* connection = new QWebSocketAdapter(socket);

    clients.insert(socket, connection);

    connect(socket, &QWebSocket::textMessageReceived, this, &QWebServerAdapter::newMessage);
    connect(socket, &QWebSocket::disconnected, this, &QWebServerAdapter::onDisconnect);

    if (receiver) receiver->newConnection(connection);
}

void QWebServerAdapter::newMessage() {
    auto *socket = reinterpret_cast<QWebSocket *>(sender());
    if (receiver) receiver->newMessage(clients[socket]);
}

void QWebServerAdapter::onDisconnect() {
    auto *socket = reinterpret_cast<QWebSocket *>(sender());
    if (receiver) receiver->onDisconnect(clients[socket]);
    clients.remove(socket);
}

void QWebServerAdapter::setReceiver(EventSocketServerReceiver *receiver) {
    this->receiver = receiver;
}

void QWebServerAdapter::onSslError(const QList<QSslError> &errors) {
    qInfo() << "SSL Error: " << errors;
}
