cmake_minimum_required(VERSION 3.5)

project(Texnopark_cpp_project LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.


SET(QT5_MODULES Widgets PrintSupport)
FIND_PACKAGE(Qt5 REQUIRED COMPONENTS ${QT5_MODULES})

include_directories(
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
    )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
find_package(Boost 1.71.0 REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
find_package (Boost REQUIRED COMPONENTS system filesystem)
add_subdirectory(../prisonDataMatrixGenerator  [EXCLUDE_FROM_ALL])
add_executable(Texnopark_cpp_project
    addproductform.cpp
    addproducttypesform.cpp
    allproductstab.cpp
    authorizationform.cpp
    controllerforbarecode.cpp
    controllerfordatabase.cpp
    main.cpp
    mainwindow.cpp
    productsbytypestab.cpp
    producttab.cpp
    producttypestab.cpp

    addproductform.h
    addproducttypesform.h
    allproductstab.h
    authorizationform.h
    controllerforbarecode.h
    controllerfordatabase.h
    mainwindow.h
    productsbytypestab.h
    producttab.h
    producttypestab.h
    structuresForTable.h
    )


target_link_libraries(Texnopark_cpp_project  Qt5::Widgets Qt5::PrintSupport KF5::Prison)
