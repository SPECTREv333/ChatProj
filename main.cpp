#include <QApplication>
#include <QPushButton>
#include "server/ChatServer.h"
#include "client_api/ChatAPI.h"
#include "ChatRegister.h"
#include "gui/ChatRegisterController.h"
#include "gui/chatregisterview.h"
#include "client/ChatApp.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ChatApp chatApp1(nullptr);

    chatApp1.show();

    return QApplication::exec();
}
