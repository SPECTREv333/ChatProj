//
// Created by leonardo on 05/09/23.
//

#ifndef CHATPROJ_QWEBSOCKETADAPTER_H
#define CHATPROJ_QWEBSOCKETADAPTER_H

#include <QObject>
#include <QWebSocket>
#include <QQueue>
#include "EventSocket.h"

class QWebSocketAdapter : public QObject, public EventSocket {
Q_OBJECT
public:
    explicit QWebSocketAdapter(std::string serverAddress = "localhost", int serverPort = 6666, QObject *parent = nullptr);

    QWebSocketAdapter(QWebSocket *socket, QObject *parent = nullptr);

    const std::string read() override;

    void write(const std::string &message) override;

    void setReceiver(EventSocketReceiver *receiver) override;

private slots:

    void newMessage(const QString& message);

    void onDisconnect();

    void onConnected();

private:
    QWebSocket* socket;
    EventSocketReceiver* receiver = nullptr;
    QQueue<QString> messages;

};


#endif //CHATPROJ_QWEBSOCKETADAPTER_H
