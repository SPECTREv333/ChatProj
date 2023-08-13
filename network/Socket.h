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

//TODO: add a connect(address, port) method

class Socket : public QObject, public Subject {
Q_OBJECT

public:
    explicit Socket(const std::string &serverAddress = "localhost", int serverPort = 6666,
                    QObject *parent = nullptr);

    ~Socket() override;

    const bool isConnected() const;

    const std::string syncread();

    const std::string read();

    void write(const std::string &message);

    void addObserver(Observer *observer) override;

    void removeObserver(Observer *observer) override;

    void notify() override;

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
