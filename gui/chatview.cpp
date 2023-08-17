//
// Created by Leonardo on 17/08/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatView.h" resolved

#include "chatview.h"
#include "ui_ChatView.h"

ChatView::~ChatView() {
    delete ui;
}

ChatView::ChatView(Chat *model, ChatController *controller, QWidget *parent) : model(model), controller(controller), QWidget(parent), ui(new Ui::ChatView) {
    ui->setupUi(this);
    model->addObserver(this);
    connect(ui->sendButton, SIGNAL(pressed()), this, SLOT(onSendPressed()));
    connect(ui->input, SIGNAL(returnPressed()), this, SLOT(onSendPressed()));
}

void ChatView::update() {
    QTextEdit* textEdit = ui->textEdit;
    textEdit->append(("<bold><" + model->getMessages().back()->getSender().getNickname() + ">:</bold>").c_str());
    textEdit->append(model->getMessages().back()->getContent().c_str());
}

void ChatView::onSendPressed() {
    controller->send(ui->input->text().toStdString());
    ui->input->clear();
}
