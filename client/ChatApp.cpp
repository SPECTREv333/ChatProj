//
// Created by Leonardo on 15/08/23.
//

#include "ChatApp.h"
#include "SignXDialog.h"
#include "QTcpSocketAdapter.h"
#include <QDialog>
#include <QFormLayout>
#include <QMessageBox>
#include <QDialogButtonBox>

ChatApp::ChatApp(QWidget *parent) : QMainWindow(parent) {
    chatAPI = nullptr;
    setWindowTitle("ChatApp");

    try {
        connectDialog();
    } catch (const std::runtime_error& e){
        QMessageBox::critical(this, "Error", e.what());
    }

    if (chatAPI == nullptr)
        close();

    chatRegister = new ChatRegister();

    chatAPI->setMediator(this);
    auto *signDialog = new SignXDialog(chatAPI, this);
    signDialog->exec();

}

void ChatApp::notify(Component *sender, const std::string &event) {
    if (sender == chatAPI){
        if (event == "newMessage"){
            chatRegister->addMessage(*chatAPI->receiveMessage());
        } else if (event == "signedIn"){
            chatRegister->setCurrentUser(chatAPI->getCurrentUser());
            chatRegisterController = new ChatRegisterController(chatRegister, chatAPI); //FIXME: dangling pointer
            chatRegisterView = new ChatRegisterView(chatRegister, chatRegisterController, this);
            setWindowTitle("Hello, " + QString::fromStdString(chatRegister->getCurrentUser().getNickname()) + "!");
            setCentralWidget(chatRegisterView);
        } else if (event == "signInFailed"){
            chatRegister->setCurrentUser(User());
            setWindowTitle("ChatApp");
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("Sign in failed");
            msgBox.exec();
        } else if (event == "disconnect"){
            QMessageBox::information(this, "Disconnected", "Connection lost");
            close();
        }
    }
}

void ChatApp::connectDialog() {
    auto *dialog = new QDialog(this);
    dialog->setWindowTitle("Connect to server");
    auto *formLayout = new QFormLayout(dialog);
    auto *addressEdit = new QLineEdit(dialog);
    auto *portEdit = new QLineEdit(dialog);
    formLayout->addRow("Address:", addressEdit);
    formLayout->addRow("Port:", portEdit);
    auto *buttonBox = new QDialogButtonBox(dialog);
    buttonBox->addButton("Connect", QDialogButtonBox::AcceptRole);
    buttonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    formLayout->addRow(buttonBox);
    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    if (dialog->exec() == QDialog::Accepted){
        if (addressEdit->text().isEmpty() || portEdit->text().isEmpty()){
            QMessageBox::warning(this, "Error", "Address and port must be specified");
            close();
        }
        delete chatAPI;
        chatAPI = new ChatAPI(new QTcpSocketAdapter(addressEdit->text().toStdString(), portEdit->text().toInt()));
    }
}

ChatApp::~ChatApp() {
    // chatRegisterView needs to be deleted before its model (chatRegister)
    // because it is an observer of chatRegister
    if (chatRegisterView != nullptr)
        delete chatRegisterView;
    delete chatAPI;
    delete chatRegister;
    delete chatRegisterController;
}


