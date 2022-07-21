cmake_minimum_required(VERSION 3.22)
project(SBrowser2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-backtrace-limit=0")

add_subdirectory(src/ext)
add_subdirectory(src/javascript)
add_subdirectory(third_party)

include_directories(src)

# special case to find qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# link 2nd and 3rd party source files
file(GLOB_RECURSE FIRST_PARTY_SOURCE_FILES src/*.cpp)

# generate the exe
add_executable(${PROJECT_NAME} main.cpp ${FIRST_PARTY_SOURCE_FILES})

# link the 2nd / 3rd party libraries to the project
target_link_libraries(${PROJECT_NAME} ext javascript web_apis) # my libs
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets Qt6::Gui) # qt
target_link_libraries(${PROJECT_NAME} magic_enum range-v3 v8pp) # 3rd party miscellaneous
target_link_libraries(${PROJECT_NAME} concurrent_queue plf_stack tsl::robin_map tuplet::tuplet veque) # containers
target_link_libraries(${PROJECT_NAME} function2 swl-variant thread-pool) # other stl replacements
