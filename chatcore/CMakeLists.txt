cmake_minimum_required(VERSION 3.25)
project(ChatLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Network
        REQUIRED)

set(SOURCE_FILES model/Chat.cpp
        model/Chat.h
        model/ChatRegister.cpp
        model/ChatRegister.h
        model/Message.h
        model/User.cpp
        model/User.h
        network/EventSocket.h
        network/EventSocketServer.h
        network/Socket.cpp
        network/Socket.h
        network/SocketServer.cpp
        network/SocketServer.h
        protocol/Packet.h
        protocol/PacketFactory.cpp
        protocol/PacketFactory.h
        protocol/concrete_packets/MessagePacket.h
        protocol/concrete_packets/SignIn.h
        protocol/concrete_packets/SignOut.h
        protocol/concrete_packets/SignUp.h
        protocol/concrete_packets/SignXResponse.h
        protocol/concrete_packets/UserList.h
        protocol/concrete_packets/UserListResponse.h
)

add_library(ChatLib STATIC ${SOURCE_FILES})

target_link_libraries(ChatLib
        Qt::Core
        Qt::Network
)
