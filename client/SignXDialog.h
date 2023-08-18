//
// Created by Leonardo on 18/08/23.
//

#ifndef CHATPROJ_SIGNXDIALOG_H
#define CHATPROJ_SIGNXDIALOG_H

#include <QDialog>
#include <QtWidgets/QLineEdit>
#include <QPushButton>
#include "../client_api/ChatAPI.h"

class SignXDialog : public QDialog {
Q_OBJECT
public:
    explicit SignXDialog(ChatAPI *api, QWidget *parent = nullptr);

public slots:

    void onSignUp();

    void onSignIn();

private:
    ChatAPI *api;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *signInButton;
    QPushButton *signUpButton;
    QPushButton *cancelButton;

};


#endif //CHATPROJ_SIGNXDIALOG_H
