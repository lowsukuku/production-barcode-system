cmake_minimum_required(VERSION 3.15)
project(FinalProject_server_part)

set(CMAKE_CXX_STANDARD 17)




find_package(Boost 1.65.1 COMPONENTS system thread REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(FinalProject_server_part main.cpp server.cpp server.h client.cpp client.h scaner.cpp scaner.h user.cpp user.h)
    target_link_libraries(FinalProject_server_part ${Boost_LIBRARIES})
endif()