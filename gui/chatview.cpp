//
// Created by Leonardo on 17/08/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatView.h" resolved

#include "chatview.h"
#include "ui_ChatView.h"

ChatView::~ChatView() {
    delete ui;
}

ChatView::ChatView(Chat *model, ChatController *controller, QWidget *parent) : model(model), controller(controller),
                                                                               QMainWindow(parent), ui(new Ui::ChatView) {
    ui->setupUi(this);
    model->addObserver(this);

    for (auto &message : model->getMessages()) {
        ui->textEdit->insertHtml(QString::fromStdString("<b>" + message->getSender().getNickname()
                                                    + "</b>: " + message->getContent() + "<br>"));
    }

    connect(ui->sendButton, SIGNAL(pressed()), this, SLOT(onSendPressed()));
    connect(ui->input, SIGNAL(returnPressed()), this, SLOT(onSendPressed()));
}

void ChatView::update() {
    QTextEdit *textEdit = ui->textEdit;
    textEdit->insertHtml(QString::fromStdString("<b>" + model->getMessages().back()->getSender().getNickname()
                                                + "</b>: " + model->getMessages().back()->getContent() + "<br>"));
    textEdit->ensureCursorVisible();
}

void ChatView::onSendPressed() {
    controller->send(ui->input->text().toStdString());
    ui->input->clear();
}
