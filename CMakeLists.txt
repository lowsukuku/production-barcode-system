cmake_minimum_required(VERSION 3.15)
project(DB)

#configure_file(CMakeLists.txt.in
#        googletest-download/CMakeLists.txt)
#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#
#add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#        ${CMAKE_BINARY_DIR}/googletest-build)
#
#enable_testing()
#add_subdirectory(test)
#
#set(CMAKE_CXX_STANDARD 14)

add_executable(DB User/User.cpp
#        User/User.h
#        User/UserMapper.cpp
#        User/UserMapper.h
        MySQL/MySQL.cpp
        MySQL/MySQL.h
        Product/Product.cpp
        Product/Product.h
#        Product/ScanerProductMapper.cpp
#        Product/ScanerProductMapper.h
        Product/ProductMapper.cpp
        Product/ProductMapper.h
#        Scaner/Scaner.cpp
#        Scaner/Scaner.h
#        Scaner/ScanerMapper.cpp
#        Scaner/ScanerMapper.h
#        err_code.h
#        test/test_Product_class.cpp
#        test/test_Scaner_class.cpp
#        test/test_User_class.cpp
#        test/test_UserMapper_class.cpp
#        test/test_ScanerMapper_class.cpp
#        test/test_ScanerProductMapper_class.cpp
#        test/test_UserProductMapper_class.cpp
        ../main.cpp MySQL/MySQL.cpp MySQL/MySQL.h)

target_link_libraries(DB mysqlcppconn)