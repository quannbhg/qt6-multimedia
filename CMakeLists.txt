cmake_minimum_required(VERSION 3.21)

project(MultimediaApp VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Multimedia Sql Network)

qt_standard_project_setup(REQUIRES 6.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(modules/domain)
add_subdirectory(modules/infrastructure)
add_subdirectory(modules/services)
add_subdirectory(modules/viewmodels)
add_subdirectory(app)
