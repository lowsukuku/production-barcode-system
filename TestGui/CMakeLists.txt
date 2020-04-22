cmake_minimum_required(VERSION 3.5)

project(gui_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5Test REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(gui_test tst_gui_test.cpp
    ../Texnopark_cpp_project/addproductform.h
    ../Texnopark_cpp_project/addproducttypesform.h
    ../Texnopark_cpp_project/allproductstab.h
    ../Texnopark_cpp_project/authorizationform.h
    ../Texnopark_cpp_project/controllerforbarecode.h
    ../Texnopark_cpp_project/controllerfordatabase.h
    ../Texnopark_cpp_project/mainwindow.h
    ../Texnopark_cpp_project/productsbytypestab.h
    ../Texnopark_cpp_project/producttab.h
    ../Texnopark_cpp_project/producttypestab.h

    ../Texnopark_cpp_project/addproductform.cpp
    ../Texnopark_cpp_project/addproducttypesform.cpp
    ../Texnopark_cpp_project/allproductstab.cpp
    ../Texnopark_cpp_project/authorizationform.cpp
    ../Texnopark_cpp_project/controllerforbarecode.cpp
    ../Texnopark_cpp_project/controllerfordatabase.cpp
    ../Texnopark_cpp_project/mainwindow.cpp
    ../Texnopark_cpp_project/productsbytypestab.cpp
    ../Texnopark_cpp_project/producttab.cpp
    ../Texnopark_cpp_project/producttypestab.cpp)
add_test(NAME gui_test COMMAND gui_test)

target_link_libraries(gui_test PRIVATE Qt5::Gui Qt5::Test Qt5::Widgets)

target_include_directories(gui_test PRIVATE ../Texnopark_cpp_project/)
