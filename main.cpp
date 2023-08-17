#include <QApplication>
#include <QPushButton>
#include "server/ChatServer.h"
#include "client_api/ChatAPI.h"
#include "model/ChatRegister.h"
#include "gui/ChatRegisterController.h"
#include "gui/chatregisterview.h"
#include "client/ChatApp.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ChatAPI chatAPI1;
    chatAPI1.signIn("user1", "pass1");
    auto* chatRegister1 = new ChatRegister(chatAPI1.getCurrentUser());

    ChatAPI chatAPI2;
    chatAPI2.signIn("user2", "pass2");
    qDebug() << "current:" << QString::fromStdString(chatAPI2.getCurrentUser().getNickname());
    //print user id to verify that the user is the same
    qDebug() << "current:" << chatAPI2.getCurrentUser().getId();
    auto* chatRegister2 = new ChatRegister(chatAPI2.getCurrentUser());

    exit(0);

    ChatApp chatApp1(&chatAPI1, chatRegister1, dynamic_cast<QWidget*>(&a));

    chatApp1.show();

    ChatApp chatApp2(&chatAPI2, chatRegister2, dynamic_cast<QWidget*>(&a));

    chatApp2.show();

    return QApplication::exec();
}
