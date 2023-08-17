//
// Created by Leonardo on 17/08/23.
//

#include <QCoreApplication>
#include "ChatServer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    UsersDatabase db;

    db.registerUser("user1", "pass1", nullptr);

    if(db.authenticate("user1", "pass1", nullptr))
        qDebug() << "User authenticated";
    else
        qDebug() << "User not authenticated";

    ChatServer server(6666);

    return QCoreApplication::exec();
}
