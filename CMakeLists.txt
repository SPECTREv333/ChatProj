cmake_minimum_required(VERSION 3.25)
project(ChatProj)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


include_directories(patterns protocol)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_executable(ChatProj main.cpp protocol/Packet.h protocol/PacketFactory.cpp protocol/PacketFactory.h model/User.cpp model/User.h protocol/concrete_packets/SignUp.h protocol/concrete_packets/SignXResponse.h patterns/Mediator.h client_api/ChatAPI.cpp client_api/ChatAPI.h model/Message.h network/ObservableSocket.h patterns/Subject.h patterns/Observer.h network/SimpleSocket.cpp network/SimpleSocket.h network/Socket.cpp protocol/concrete_packets/SignIn.h protocol/concrete_packets/SignOut.h protocol/concrete_packets/UserList.h protocol/concrete_packets/UserListResponse.h protocol/concrete_packets/MessagePacket.h
        network/EventSocketServer.h
        network/SocketServer.h
        network/SocketServer.cpp
        server/ChatServer.cpp
        server/ChatServer.h)
target_link_libraries(ChatProj
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        )

