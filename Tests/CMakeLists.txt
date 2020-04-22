cmake_minimum_required(VERSION 3.5)

project(MyTest LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DGTEST_LANGUAGE_CXX11)

#find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(lib/googletest)

#if ($ENV{GOOGLETEST_DIR})
#    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
#else ()
#    if (NOT "" STREQUAL "")
#        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
#    endif ()
#    set(GOOGLETEST_DIR "")
#endif ()
#if (EXISTS ${GOOGLETEST_DIR})
#    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
#    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
#elseif (UNIX AND EXISTS /usr/src/gtest)
#    set(GTestSrc /usr/src/gtest)
#    message(WARNING "Using gtest from system")
#    if (EXISTS /usr/src/gmock)
#        set(GMockSrc /usr/src/gmock)
#    endif ()
#else ()
#    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
#endif ()

#set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
#set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
#if (NOT ${GMockSrc} STREQUAL "")
#    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
#    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
#endif ()



add_executable(MyTest  tst_mytest.h
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
    ../Texnopark_cpp_project/producttypestab.cpp


    )
#               ${GTestFiles})
target_link_libraries(MyTest PRIVATE Qt5::Widgets gtest gmock gtest_main)
#target_link_libraries(MyTest PRIVATE Threads::Threads gtest gmock Qt5::Widgets)
#add_test(NAME MyTest COMMAND MyTest)


target_include_directories(MyTest PRIVATE ../Texnopark_cpp_project/)




