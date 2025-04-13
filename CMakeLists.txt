cmake_minimum_required(VERSION 3.10)

project(mcpxx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC")

find_package(nlohmann_json REQUIRED)

file(GLOB_RECURSE SRC
    "src/**.cpp"
)

add_library(mcpxx SHARED ${SRC})

target_link_libraries(mcpxx PRIVATE nlohmann_json::nlohmann_json)

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