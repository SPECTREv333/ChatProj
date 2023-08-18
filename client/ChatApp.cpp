//
// Created by Leonardo on 15/08/23.
//

#include "ChatApp.h"
#include "SignXDialog.h"
#include <QDialog>
#include <QFormLayout>
#include <QMessageBox>
#include <QDialogButtonBox>

ChatApp::ChatApp(QWidget *parent) : QMainWindow(parent) {
    chatAPI = nullptr;
    setWindowTitle("ChatApp");

    connectDialog();

    if (chatAPI == nullptr)
        exit(0);

    chatRegister = new ChatRegister();

    chatAPI->setMediator(this);
    SignXDialog *signDialog = new SignXDialog(chatAPI, this);
    signDialog->exec();

    setCentralWidget(chatRegisterView);

}

void ChatApp::notify(Component *sender, const std::string &event) {
    if (sender == chatAPI){
        if (event == "newMessage"){
            chatRegister->addMessage(chatAPI->receiveMessage());
        } else if (event == "signedIn"){
            chatRegister->setCurrentUser(chatAPI->getCurrentUser());
            chatRegisterController = new ChatRegisterController(chatRegister, chatAPI); //FIXME: dangling pointer
            chatRegisterView = new ChatRegisterView(chatRegister, chatRegisterController, this);
            setWindowTitle("Hello, " + QString::fromStdString(chatRegister->getCurrentUser().getNickname()) + "!");
        } else if (event == "signInFailed"){
            chatRegister->setCurrentUser(User());
            setWindowTitle("ChatApp");
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("Sign in failed");
            msgBox.exec();
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
        if (addressEdit->text().isEmpty() || portEdit->text().isEmpty())
            QMessageBox::critical(this, "Error", "Address and port must be specified");
        delete chatAPI;
        chatAPI = new ChatAPI(addressEdit->text().toStdString(), portEdit->text().toInt());
    }
}


