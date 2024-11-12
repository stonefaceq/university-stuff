cmake_minimum_required(VERSION 3.27)
project(db)

set(CMAKE_CXX_STANDARD 17)
include_directories(Headers)

add_executable(db main.cpp
        Headers/Monkey.h
        Headers/Const.h
        Headers/Funcs.h
        Headers/Node.h
        Headers/Menu.h
        Headers/Family.h
        Headers/Queue.h
        Headers/Utils.h
        Sources/Monkey.cpp
        Sources/Funcs.cpp
        Sources/Node.cpp
        Sources/Menu.cpp
        Sources/Family.cpp
        Sources/Queue.cpp
        Sources/Utils.cpp
        Sources/threads.cpp)
