cmake_minimum_required(VERSION 3.10)
project(Babel)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(babel_client client/main.cpp)
target_include_directories(babel_client PUBLIC ${CONAN_INCLUDE_DIRS})
target_link_directories(babel_client PUBLIC ${CMAKE_BINARY_DIR}/bin/lib)
target_link_libraries(babel_client CONAN_PKG::portaudio CONAN_PKG::opus Qt5::Widgets)

add_executable(babel_server server/main.cpp)
target_include_directories(babel_server PUBLIC ${CONAN_INCLUDE_DIRS})
target_link_directories(babel_server PUBLIC ${CMAKE_BINARY_DIR}/bin/lib)
target_link_libraries(babel_server CONAN_PKG::asio CONAN_PKG::sqlite_orm)