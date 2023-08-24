//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_QTCPSERVERADAPTER_H
#define CHATPROJ_QTCPSERVERADAPTER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include "Mediator.h"
#include "EventSocketReceiver.h"
#include "EventSocketServer.h"
#include "QTcpSocketAdapter.h"

// It really just was all along an adapter for QTcpServer

class QTcpServerAdapter : public QObject, public EventSocketServer {
Q_OBJECT

public:
    explicit QTcpServerAdapter(int port, EventSocketReceiver* mediator = nullptr);

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


#endif //CHATPROJ_QTCPSERVERADAPTER_H
