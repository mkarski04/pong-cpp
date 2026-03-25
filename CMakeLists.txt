cmake_minimum_required(VERSION 4.1)
project(pong)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
)

set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(SFML)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(pong main.cpp)

target_link_libraries(pong PRIVATE sfml-graphics sfml-window sfml-system)