//
// Created by leonardo on 05/09/23.
//

#ifndef CHATPROJ_QWEBSERVERADAPTER_H
#define CHATPROJ_QWEBSERVERADAPTER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include "EventSocketServer.h"

class QWebServerAdapter : public QObject, public EventSocketServer{
    Q_OBJECT
public:
    explicit QWebServerAdapter(int port, EventSocketServerReceiver* mediator = nullptr);

    void setReceiver(EventSocketServerReceiver *receiver) override;

    void addConnection(QWebSocket *socket);

public slots:

    void newMessage();

    void onDisconnect();

    void newConnection();

    void onSslError(const QList<QSslError> &errors);

private:
    EventSocketServerReceiver *receiver;
    QWebSocketServer *server;
    QMap<QWebSocket *, EventSocket*> clients;

};


#endif //CHATPROJ_QWEBSERVERADAPTER_H
