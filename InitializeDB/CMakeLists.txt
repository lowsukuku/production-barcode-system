cmake_minimum_required(VERSION 3.15)
project(DB_test)

set(CMAKE_CXX_STANDARD 17)

find_library(MYSQL_LIBRARY
        NAMES mysql libmysql
        PATHS ${CMAKE_PREFIX_PATH}
        )

find_path(MYSQL_INCLUDE_DIR
        NAMES mysql.h
        PATHS ${CMAKE_PREFIX_PATH}
        )

add_executable(DB_test main.cpp)

target_link_libraries(DB_test mysqlconn)