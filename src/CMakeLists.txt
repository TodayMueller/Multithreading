cmake_minimum_required(VERSION 3.28.1)
project(multithreating LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Server)
add_subdirectory(Client)
