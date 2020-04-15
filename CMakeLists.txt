cmake_minimum_required(VERSION 3.15)
project(FinalProject_server_part)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++17 -Wall -ggdb3 -pthread")
include_directories(Tests)
include_directories(/usr/local/include)
include_directories(/usr/local/opt/openssl@1.1/include)

link_directories(/usr/local/lib /usr/local/opt/openssl@1.1/lib)

find_package(OpenSSL REQUIRED)


add_executable(FinalProject_server_part main.cpp
        Server/server.cpp Server/server.h
        Server/Client/client.cpp Server/Client/client.h
        Server/Client/Scaner/scaner.cpp Server/Client/Scaner/scaner.h
        Server/Client/User/user.cpp Server/Client/User/user.h
        Server/HttpHandler/httphandler.cpp Server/HttpHandler/httphandler.h
        Server/Client/Router/router.cpp Server/Client/Router/router.h)


target_link_libraries(FinalProject_server_part ${OPENSSL_LIBRARIES})
target_link_libraries(FinalProject_server_part -lboost_system -lpthread -std=c++17)


set(CMAKE_CXX_FLAGS "-g -Wall -DBOOST_LOG_DYN_LINK")

add_subdirectory(Tests)