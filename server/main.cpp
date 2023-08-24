//
// Created by Leonardo on 17/08/23.
//

#include <QCoreApplication>
#include "ChatServer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    ChatServer server(new QTcpServerAdapter(6666));

    return QCoreApplication::exec();
}
