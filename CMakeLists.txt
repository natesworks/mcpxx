cmake_minimum_required(VERSION 3.10)

project(mcpxx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC")

file(GLOB_RECURSE SRC
    "src/**.cpp"
)

add_library(mcpxx SHARED ${SRC})

set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "Installation directory" FORCE)

install(TARGETS mcpxx
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY src/
    DESTINATION include/mcpxx
    FILES_MATCHING PATTERN "*.h"
)