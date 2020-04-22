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

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()


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




