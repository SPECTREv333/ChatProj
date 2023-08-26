//
// Created by Leonardo on 13/08/23.
//

#ifndef CHATPROJ_CHATAPI_H
#define CHATPROJ_CHATAPI_H

#include <map>
#include <list>
#include "Mediator.h"
#include "User.h"
#include "Message.h"
#include "EventSocket.h"
#include "concrete_packets/SignXResponse.h"
#include "concrete_packets/MessagePacket.h"
#include "concrete_packets/UserListResponse.h"

// facade for client side
class ChatAPI : public EventSocketReceiver, public Component {
public:
    explicit ChatAPI(EventSocket *socket);

    ~ChatAPI() override;

    void signUp(const std::string &nickname, const std::string &password);

    void signIn(const std::string &nickname, const std::string &password);

    void signOut();

    void sendMessage(const Message &message);

    Message *receiveMessage();

    void refreshUsers();

    const User &getCurrentUser() const;

    std::list<User> getUsers() const;

    void newMessage() override;

    void onDisconnect() override;

private:

    void newPacket();
    void handleSignXResponse(SignXResponse *response);
    void handleMessagePacket(MessagePacket *packet);
    void handleUserListResponse(UserListResponse *packet);

    User currentUser;
    EventSocket *socket;
    std::map<int, User> users;
    Message *lastMessage;

};


#endif //CHATPROJ_CHATAPI_H
