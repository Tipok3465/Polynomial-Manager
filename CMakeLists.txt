cmake_minimum_required(VERSION 3.26)
project(PolManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(PolManager main.cpp
        header.h
        App.cpp
        App.h
        Polynomial.cpp
        Polynomial.h
        Node.h
        Node.cpp)

target_link_libraries(PolManager
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

