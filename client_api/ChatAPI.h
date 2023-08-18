//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_CHATAPI_H
#define CHATPROJ_CHATAPI_H

#include <map>
#include <list>
#include "Mediator.h"
#include "../model/User.h"
#include "../model/Message.h"
#include "../network/ObservableSocket.h"
#include "concrete_packets/SignXResponse.h"
#include "concrete_packets/MessagePacket.h"
#include "concrete_packets/UserListResponse.h"

//TODO: use ObservableSocket to do comunication, MAKE SURE SERVER WORKS FIRST!!

// facade for client side
class ChatAPI : public Component, public Observer {
public:
    explicit ChatAPI(const std::string& address = "127.0.0.1", int port = 6666);

    ~ChatAPI() override;

    void signUp(const std::string &nickname, const std::string &password);

    void signIn(const std::string &nickname, const std::string &password);

    void signOut();

    void sendMessage(const Message &message);

    Message *receiveMessage();

    void refreshUsers();

    const User &getCurrentUser() const;

    std::list<User> getUsers() const;

    void update() override;

private:

    void handleSignXResponse(SignXResponse *response);
    void handleMessagePacket(MessagePacket *packet);
    void handleUserListResponse(UserListResponse *packet);

    User currentUser;
    ObservableSocket *socket;
    std::map<int, User> users;
    Message *lastMessage;


};


#endif //CHATPROJ_CHATAPI_H
