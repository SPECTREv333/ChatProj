//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_SOCKETSERVER_H
#define CHATPROJ_SOCKETSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include "Mediator.h"
#include "EventSocketServer.h"

class SocketServer : public QObject, public Component {
Q_OBJECT

public:
    SocketServer(int port, EventSocketServer* mediator);

    void addConnection(QTcpSocket *socket);

public slots:

    void newMessage();

    void onDisconnect();

    void newConnection();

private:
    EventSocketServer *eventSocketServer;
    QTcpServer *server;
    QMap<QTcpSocket *, ObservableSocket*> clients;
};


#endif //CHATPROJ_SOCKETSERVER_H
