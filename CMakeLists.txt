cmake_minimum_required(VERSION 3.25)
project(ChatProj)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(chatcore/protocol chatcore/network chatcore/model patterns)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_subdirectory(chatcore)

set(CLIENT_SOURCES
        client/ChatApp.cpp
        client/ChatApp.h
        client/SignXDialog.cpp
        client/SignXDialog.h
        client_api/ChatAPI.cpp
        client_api/ChatAPI.h
        gui/ChatController.cpp
        gui/ChatController.h
        gui/ChatRegisterController.cpp
        gui/ChatRegisterController.h
        gui/chatregisterview.cpp
        gui/chatregisterview.h
        gui/chatregisterview.ui
        gui/chatview.cpp
        gui/chatview.h
        gui/chatview.ui
        patterns/Mediator.h
        patterns/Observer.h
        patterns/Subject.h
)

set(SERVER_SOURCES
        server/ChatServer.cpp
        server/ChatServer.h
        server/UserEntry.cpp
        server/UserEntry.h
        server/UsersDatabase.cpp
        server/UsersDatabase.h
        patterns/Mediator.h
        patterns/Observer.h
        patterns/Subject.h
)

add_executable(ChatProj main.cpp ${CLIENT_SOURCES})

add_executable(ChatServer server/main.cpp ${SERVER_SOURCES})

target_link_libraries(ChatServer
        Qt::Core
        Qt::Network
        ChatLib
)

target_link_libraries(ChatProj
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        ChatLib
        )

