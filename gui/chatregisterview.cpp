//
// Created by Leonardo on 15/08/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatRegisterView.h" resolved

#include "chatregisterview.h"
#include "ui_ChatRegisterView.h"


ChatRegisterView::ChatRegisterView(ChatRegister *model, ChatRegisterController* controller, QWidget *parent) :
        model(model), controller(controller), QWidget(parent), ui(new Ui::ChatRegisterView) {
    ui->setupUi(this);
    model->addObserver(this);
    setWindowTitle("Hello, " + QString::fromStdString(model->getCurrentUser().getNickname()) + "!");
    connect(ui->refreshButton, &QPushButton::pressed, this, &ChatRegisterView::onRefreshPressed);
    connect(ui->openButton, &QPushButton::pressed, this, &ChatRegisterView::onOpenPressed);
}

ChatRegisterView::~ChatRegisterView() {
    model->removeObserver(this);
    delete ui;
}

void ChatRegisterView::update() {
    //ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    for (auto& chat : model->getChats()) {
        auto* id = new QTableWidgetItem(QString::number(chat->getRemoteUser().getId()));
        auto* nickname = new QTableWidgetItem(chat->getRemoteUser().getNickname().c_str());
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, id);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, nickname);
    }
}

void ChatRegisterView::onRefreshPressed() {
    controller->refresh();
}

void ChatRegisterView::onOpenPressed() {
    auto selected = ui->tableWidget->selectedItems();
    if (!selected.empty()) {
        auto id = selected.at(0)->text().toInt();
        controller->openChat(id, this);
    }
}
