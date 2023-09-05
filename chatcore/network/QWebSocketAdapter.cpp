//
// Created by leonardo on 05/09/23.
//

#include <QFile>
#include "QWebSocketAdapter.h"

QWebSocketAdapter::QWebSocketAdapter(std::string serverAddress, int serverPort, QObject *parent) {
    socket = new QWebSocket("", QWebSocketProtocol::VersionLatest, parent);
    connect(socket, &QWebSocket::connected, this, &QWebSocketAdapter::onConnected);
    QSslConfiguration sslConfiguration;
    QFile certFile(QStringLiteral("cert.pem"));
    certFile.open(QIODevice::ReadOnly);
    QSslCertificate certificate(&certFile, QSsl::Pem);
    certFile.close();
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.addCaCertificate(certificate);
    socket->setSslConfiguration(sslConfiguration);
    socket->open(QUrl(QString::fromStdString("wss://" + serverAddress + ":" + std::to_string(serverPort))));
}

void QWebSocketAdapter::onConnected() {
    qInfo() << "Connected!";
    connect(socket, &QWebSocket::textMessageReceived, this, &QWebSocketAdapter::newMessage);
    connect(socket, &QWebSocket::disconnected, this, &QWebSocketAdapter::onDisconnect);
}

const std::string QWebSocketAdapter::read() {
    return messages.dequeue().toStdString();
}

void QWebSocketAdapter::write(const std::string &message) {
    socket->sendTextMessage(QString::fromStdString(message));
}

void QWebSocketAdapter::setReceiver(EventSocketReceiver *receiver) {
    this->receiver = receiver;
}

void QWebSocketAdapter::newMessage(const QString& message) {
    messages.enqueue(message);
    if (receiver)
        receiver->newMessage();
}

void QWebSocketAdapter::onDisconnect() {
    if (receiver)
        receiver->onDisconnect();
}

QWebSocketAdapter::QWebSocketAdapter(QWebSocket *socket, QObject *parent) {
    socket->setParent(this);
    this->socket = socket;
    connect(this->socket, &QWebSocket::textMessageReceived, this, &QWebSocketAdapter::newMessage);
    connect(this->socket, &QWebSocket::disconnected, this, &QWebSocketAdapter::onDisconnect);
}


