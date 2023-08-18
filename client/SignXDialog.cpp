//
// Created by Leonardo on 18/08/23.
//

#include <QFormLayout>
#include <QDialogButtonBox>
#include "SignXDialog.h"

SignXDialog::SignXDialog(ChatAPI *api, QWidget *parent) : api(api), QDialog(parent) {
    setWindowTitle("Welcome");

    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    signInButton = new QPushButton(this);
    signUpButton = new QPushButton(this);
    cancelButton = new QPushButton(this);

    auto *formLayout = new QFormLayout(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    formLayout->addRow("Username:", usernameEdit);
    formLayout->addRow("Password:", passwordEdit);

    signInButton->setText("Sign In");
    signUpButton->setText("Sign Up");
    cancelButton->setText("Cancel");
    auto *buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(signInButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(signUpButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);
    formLayout->addRow(buttonBox);
    connect(signInButton, SIGNAL(clicked()), this, SLOT(onSignIn()));
    connect(signUpButton, SIGNAL(clicked()), this, SLOT(onSignUp()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void SignXDialog::onSignUp() {
    std::string username = usernameEdit->text().toStdString();
    std::string password = passwordEdit->text().toStdString();
    api->signUp(username, password);
    accept();
}

void SignXDialog::onSignIn() {
    std::string username = usernameEdit->text().toStdString();
    std::string password = passwordEdit->text().toStdString();
    api->signIn(username, password);
    accept();
}


