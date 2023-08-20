//
// Created by Leonardo on 08/07/23.
// Since this project is using QT here im using QTcpSocket as it is platform indipendent
//

#ifndef CHAT_CHANNEL_H
#define CHAT_CHANNEL_H

#include <QObject>
#include <QTcpSocket>
#include "Subject.h"
#include "Mediator.h"
#include "EventSocket.h"

//TODO: add a connect(address, port) method

class Socket : public QObject, public EventSocket {
Q_OBJECT

public:
    explicit Socket(const std::string &serverAddress = "localhost", int serverPort = 6666,
                    QObject *parent = nullptr);

    explicit Socket(QTcpSocket *socket, QObject *parent = nullptr);

    ~Socket() override;

    bool isConnected() const;

    const QTcpSocket *getSocket() const;

    void setSocket(QTcpSocket *socket);

    const std::string syncread() override;

    const std::string read() override;

    void write(const std::string &message);

public slots:

    void displayError();

    void displayState();

    void newMessage();

    void onDisconnect();

private:
    QTcpSocket *socket;
    std::list<Observer *> observers;

};

#endif //CHAT_CHANNEL_H
