cmake_minimum_required(VERSION 3.15)
project(HttpServer)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_library(gumbo REQUIRED)
find_package(Boost REQUIRED COMPONENTS system log log_setup)
include_directories(${Boost_DIRECTORIES})
find_package(OpenSSL REQUIRED)

add_executable(HttpServer main.cpp
        Server/server.cpp Server/server.h
        Server/HttpHandler/httphandler.cpp Server/HttpHandler/httphandler.h
        Server/Client/Router/router.cpp Server/Client/Router/router.h
        Server/Client/client.cpp Server/Client/client.h
        Server/Client/User/user.cpp Server/Client/User/user.h
        Server/Client/Scaner/scaner.cpp Server/Client/Scaner/scaner.h

        Server/DataBase/src/err_code.h
        Server/DataBase/src/User/User.h Server/DataBase/src/User/User.cpp
        Server/DataBase/src/User/UserMapper.h Server/DataBase/src/User/UserMapper.cpp
        Server/DataBase/src/Scaner/DeviceScaner.h Server/DataBase/src/Scaner/DeviceScaner.cpp
        Server/DataBase/src/Scaner/ScanerMapper.h Server/DataBase/src/Scaner/ScanerMapper.cpp
        Server/DataBase/src/Product/Product.h Server/DataBase/src/Product/Product.cpp
        Server/DataBase/src/Product/ProductMapper.h Server/DataBase/src/Product/ProductMapper.cpp
        Server/DataBase/src/Parser/IGet.h Server/DataBase/src/Parser/IGet.cpp
        Server/DataBase/src/Parser/IPost.h Server/DataBase/src/Parser/IPost.cpp
        Server/DataBase/src/MySQL/MySQL.h Server/DataBase/src/MySQL/MySQL.cpp
        )

target_link_libraries(HttpServer OpenSSL::SSL)
target_link_libraries(HttpServer ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
target_link_libraries(HttpServer mysqlcppconn)
set(CMAKE_CXX_FLAGS "-g -Wall -DBOOST_LOG_DYN_LINK")
add_subdirectory(Tests)





