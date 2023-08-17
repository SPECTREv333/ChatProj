//
// Created by Leonardo on 17/08/23.
//

#ifndef CHATPROJ_CHATVIEW_H
#define CHATPROJ_CHATVIEW_H

#include <QMainWindow>
#include "../model/Chat.h"
#include "ChatController.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ChatView; }
QT_END_NAMESPACE

class ChatView : public QMainWindow, public Observer {
Q_OBJECT

public:
    explicit ChatView(Chat *model, ChatController *controller, QWidget *parent = nullptr);

    ~ChatView() override;

    void update() override;

public slots:

    void onSendPressed();

private:
    Chat *model;
    ChatController *controller;
    Ui::ChatView *ui;
};


#endif //CHATPROJ_CHATVIEW_H
