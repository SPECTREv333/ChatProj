//
// Created by Leonardo on 17/08/23.
//

#include <QCoreApplication>
#include <iostream>
#include "ChatServer.h"
#include "QWebServerAdapter.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    EventSocketServer *socketServer;

    // if argument is secure pass QWebSocketAdapter
    if (argc > 1 && strcmp(argv[1], "secure") == 0) {
        std::cout << "Secure mode\n" << std::endl;
        socketServer = new QWebServerAdapter(6666);
    } else {
        socketServer = new QTcpServerAdapter(6666);
    }

    ChatServer server(socketServer);

    return QCoreApplication::exec();
}
