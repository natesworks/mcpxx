cmake_minimum_required(VERSION 3.10)

project(TestServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

add_executable(TestServer main.cpp)

target_link_libraries(TestServer PRIVATE -lmcpxx)

target_compile_options(TestServer PRIVATE -g)
target_link_options(TestServer PRIVATE -g)