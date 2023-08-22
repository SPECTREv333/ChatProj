//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_SOCKETSERVER_H
#define CHATPROJ_SOCKETSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include "Mediator.h"
#include "EventSocketReceiver.h"
#include "EventSocketServer.h"
#include "Socket.h"

class SocketServer : public QObject, public EventSocketServer {
Q_OBJECT

public:
    explicit SocketServer(int port, EventSocketReceiver* mediator = nullptr);

    void addConnection(QTcpSocket *socket);

    void setMediator(EventSocketReceiver *mediator) override;

public slots:

    void newMessage();

    void onDisconnect();

    void newConnection();

private:
    EventSocketReceiver *eventSocketServer;
    QTcpServer *server;
    QMap<QTcpSocket *, EventSocket*> clients;
};


#endif //CHATPROJ_SOCKETSERVER_H
