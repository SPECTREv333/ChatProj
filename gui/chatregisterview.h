//
// Created by Leonardo on 15/08/23.
//

#ifndef CHATPROJ_CHATREGISTERVIEW_H
#define CHATPROJ_CHATREGISTERVIEW_H

#include <QWidget>
#include "ChatRegisterController.h"
#include "../model/ChatRegister.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ChatRegisterView; }
QT_END_NAMESPACE

class ChatRegisterView : public QWidget, public Observer {
Q_OBJECT

public:
    explicit ChatRegisterView(ChatRegister *model, ChatRegisterController* controller, QWidget *parent = nullptr);

    ~ChatRegisterView() override;

    void update() override;

public slots:

    void onRefreshPressed();

    void onOpenPressed();

private:
    Ui::ChatRegisterView *ui;
    ChatRegisterController* controller;
    ChatRegister* model;
};


#endif //CHATPROJ_CHATREGISTERVIEW_H
