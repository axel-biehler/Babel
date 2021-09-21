cmake_minimum_required(VERSION 3.10)
project(Babel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(babel_client client/main.cpp
        shared/Networking/RawPacket.cpp shared/Networking/RawPacket.hpp
        shared/Networking/Packet.cpp shared/Networking/Packet.hpp
        shared/Networking/RawTypes.hpp
        shared/Networking/Packets/PacketCmdRegister.cpp shared/Networking/Packets/PacketCmdRegister.hpp
        shared/Networking/ArgumentsWriter.cpp shared/Networking/ArgumentsWriter.hpp
        shared/Networking/ArgumentsReader.cpp shared/Networking/ArgumentsReader.hpp)
target_include_directories(babel_client PUBLIC ${CONAN_INCLUDE_DIRS})
target_include_directories(babel_client PUBLIC ${CMAKE_SOURCE_DIR}/shared)
target_link_directories(babel_client PUBLIC ${CMAKE_BINARY_DIR}/bin/lib)
target_link_libraries(babel_client CONAN_PKG::portaudio CONAN_PKG::opus CONAN_PKG::qt)

add_executable(babel_server server/main.cpp
        shared/Networking/RawPacket.cpp shared/Networking/RawPacket.hpp
        shared/Networking/Packet.cpp shared/Networking/Packet.hpp
        shared/Networking/RawTypes.hpp
        shared/Networking/Packets/PacketCmdRegister.cpp
        shared/Networking/Packets/PacketCmdRegister.hpp
        shared/Networking/ArgumentsReader.cpp shared/Networking/ArgumentsReader.hpp
        shared/Networking/ArgumentsWriter.cpp shared/Networking/ArgumentsWriter.hpp)
target_include_directories(babel_server PUBLIC ${CONAN_INCLUDE_DIRS})
target_include_directories(babel_server PUBLIC ${CMAKE_SOURCE_DIR}/shared)
target_link_directories(babel_server PUBLIC ${CMAKE_BINARY_DIR}/bin/lib)
target_link_libraries(babel_server CONAN_PKG::asio CONAN_PKG::sqlite_orm)