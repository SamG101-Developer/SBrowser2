cmake_minimum_required(VERSION 3.22)
project(SBrowser2)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

add_subdirectory(third_party)


# link 1st and 3rd party source files
file(GLOB_RECURSE FIRST_PARTY_SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE THIRD_PARTY_SOURCE_FILES third_party/*.cpp third_party/*.c)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

add_executable(${PROJECT_NAME} main.cpp
        ${FIRST_PARTY_SOURCE_FILES}
        ${THIRD_PARTY_SOURCE_FILES})

# link the 3rd party libraries to the project
target_link_libraries(${PROJECT_NAME} v8pp)
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets Qt6::Gui)

# no CMakeLists.txt for these libraries
include_directories(third_party/veque/include)
include_directories(third_party/robin-hood-hashing/src/include)
include_directories(third_party/robin-map/include)
