cmake_minimum_required(VERSION 3.15)
project(HttpServer)

set(CMAKE_CXX_STANDARD 11)
include_directories(Tests)
include_directories(/usr/local/include)
include_directories(/usr/local/opt/openssl@1.1/include)

link_directories(/usr/local/lib /usr/local/opt/openssl@1.1/lib)
find_package(Boost 1.62 COMPONENTS thread REQUIRED)

add_executable(HttpServer main.cpp Server/server.cpp Server/server.h Server/Client/client.cpp Server/Client/client.h Server/Client/User/user.cpp Server/Client/User/user.h Server/Client/Scaner/scaner.cpp Server/Client/Scaner/scaner.h Server/HttpHandler/httphandler.cpp Server/HttpHandler/httphandler.h Server/Client/Router/router.cpp Server/Client/Router/router.h)


target_link_libraries(HttpServer ${OPENSSL_LIBRARIES})


target_link_libraries(HttpServer -lboost_system Boost::thread -lgumbo -lcrypto -lssl -std=c++17)
add_subdirectory(Tests)