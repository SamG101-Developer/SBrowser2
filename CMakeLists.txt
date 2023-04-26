cmake_minimum_required(VERSION 3.25.2)
project(SBrowser2)

# set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /experimental:module")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_MODULE_LOCATION ${CMAKE_BINARY_DIR}/pcm)

set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

set(QT_VER 6.4.1)
set(QT_COMPONENTS Core Widgets Gui Multimedia MultimediaWidgets WebSockets)

include_directories(src)

file(GLOB_RECURSE FIRST_PARTY_MODULE_FILES src/*.ixx)
file(GLOB_RECURSE FIRST_PARTY_SOURCE_FILES src/*.cpp)

include(FetchContent)
set(FETCH_CONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/_deps)

FetchContent_Declare(Assert
        GIT_REPOSITORY https://github.com/jeremy-rifkin/libassert.git
        GIT_TAG master)

FetchContent_Declare(Expected
        GIT_REPOSITORY https://github.com/TartanLlama/expected.git
        GIT_TAG master)

FetchContent_Declare(FileSystem
        GIT_REPOSITORY https://github.com/cginternals/cppfs.git
        GIT_TAG master)

FetchContent_Declare(Function
        GIT_REPOSITORY https://github.com/Naios/function2.git
        GIT_TAG master)

FetchContent_Declare(HashMapSet
        GIT_REPOSITORY https://github.com/martinus/unordered_dense.git
        GIT_TAG main)

FetchContent_Declare(InitializerList ${FETCH_CONTENT_BASE_DIR}/initializerlist-src/better_braces
        GIT_REPOSITORY https://github.com/HolyBlackCat/better_braces.git
        GIT_TAG master)

FetchContent_Declare(Json
        GIT_REPOSITORY https://github.com/wqking/jsonpp.git
        GIT_TAG master)

FetchContent_Declare(Optional
        GIT_REPOSITORY https://github.com/TartanLlama/optional.git
        GIT_TAG master)

FetchContent_Declare(Queue SOURCE_DIR ${FETCH_CONTENT_BASE_DIR}/queue-src/plf
        GIT_REPOSITORY https://github.com/mattreecebentley/plf_queue.git
        GIT_TAG main)

FetchContent_Declare(Random
        GIT_REPOSITORY https://github.com/effolkronium/random.git
        GIT_TAG master)

FetchContent_Declare(Range
        GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
        GIT_TAG master)

FetchContent_Declare(Regex # TODO : switch to Hyper...1
        GIT_REPOSITORY https://github.com/google/re2.git
        GIT_TAG main)

FetchContent_Declare(Stack SOURCE_DIR ${FETCH_CONTENT_BASE_DIR}/stack-src/plf
        GIT_REPOSITORY https://github.com/mattreecebentley/plf_stack.git
        GIT_TAG master)

FetchContent_Declare(Streams
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master)

FetchContent_Declare(Tuple
        GIT_REPOSITORY https://github.com/codeinred/tuplet.git
        GIT_TAG main)

FetchContent_Declare(Variant
        GIT_REPOSITORY https://github.com/groundswellaudio/swl-variant.git
        GIT_TAG main)

FetchContent_Declare(Vector SOURCE_DIR ${FETCH_CONTENT_BASE_DIR}/vector-src/veque
        GIT_REPOSITORY https://github.com/Shmoopty/veque.git
        GIT_TAG master)

FetchContent_Declare(Crypto SOURCE_DIR ${FETCH_CONTENT_BASE_DIR}/crypto-src/cryptopp
        GIT_REPOSITORY https://github.com/weidai11/cryptopp.git
        GIT_TAG master)

FetchContent_Declare(DateTime
        GIT_REPOSITORY https://github.com/mobius3/asap.git
        GIT_TAG master)

FetchContent_Declare(HardwareInfo
        GIT_REPOSITORY https://github.com/lfreist/hwinfo.git
        GIT_TAG main)

FetchContent_Declare(Gamepad
        GIT_REPOSITORY https://github.com/univrsal/libgamepad.git
        GIT_TAG master)

FetchContent_Declare(MagicEnum SOURCE_DIR ${FETCH_CONTENT_BASE_DIR}/magicenum-src/magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        GIT_TAG master)

FetchContent_Declare(Qt
        GIT_REPOSITORY https://github.com/SamG101-Developer/Qt6WindowsBinaries.git
        GIT_TAG master)

FetchContent_Declare(SelfMacro
        GIT_REPOSITORY https://github.com/MitalAshok/self_macro.git
        GIT_TAG master)

FetchContent_Declare(UUIDs
        GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
        GIT_TAG master)

FetchContent_Declare(V8PP
        GIT_REPOSITORY https://github.com/pmed/v8pp.git
        GIT_TAG master)

FetchContent_MakeAvailable(
        Assert Expected FileSystem Function HashMapSet
        InitializerList Json Optional Queue Random
        Range Regex Stack Streams Tuple Variant
        Vector Crypto DateTime HardwareInfo Gamepad MagicEnum SelfMacro UUIDs V8PP) # TODO : Qt

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/${QT_VER}/msvc2019_64")
find_package(Qt6 REQUIRED COMPONENTS ${QT_COMPONENTS})


add_executable(${PROJECT_NAME} main.cpp ${FIRST_PARTY_SOURCE_FILES})

#file(COPY "${CMAKE_SOURCE_DIR}/third_party/v8-v143-x64.10.0.139.9" DESTINATION "${FETCH_CONTENT_BASE_DIR}/v8pp-build")
#file(COPY "${CMAKE_SOURCE_DIR}/third_party/v8.redist-v143-x64.10.0.139.9" DESTINATION "${FETCH_CONTENT_BASE_DIR}/v8pp-build")
file(GLOB cryptopp_src ${FETCH_CONTENT_BASE_DIR}/crypto-src/cryptopp/*.cpp)


add_library(better_braces INTERFACE)
target_include_directories(better_braces INTERFACE ${FETCH_CONTENT_BASE_DIR}/initializerlist-src/include)

add_library(plf_stack INTERFACE)
target_include_directories(plf_stack INTERFACE ${FETCH_CONTENT_BASE_DIR}/stack-src)

add_library(plf_queue INTERFACE)
target_include_directories(plf_queue INTERFACE ${FETCH_CONTENT_BASE_DIR}/queue-src)

add_library(veque INTERFACE)
target_include_directories(veque INTERFACE ${FETCH_CONTENT_BASE_DIR}/vector-src/veque/include)

add_library(bigint INTERFACE)
target_include_directories(bigint INTERFACE "${FETCH_CONTENT_BASE_DIR}/bigint-src/Big Integer Library in Single file")

add_library(crypto ${cryptopp_src})
target_include_directories(crypto PUBLIC ${FETCH_CONTENT_BASE_DIR}/crypto-src)

add_library(hwinfo INTERFACE)
target_include_directories(hwinfo INTERFACE ${FETCH_CONTENT_BASE_DIR}/hardwareinfo-src/include)

add_library(modules MODULE ${FIRST_PARTY_MODULE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
        assert expected cppfs function2::function2 unordered_dense::unordered_dense better_braces jsonpp optional
        effolkronium_random range-v3::range-v3 re2::re2 plf_stack plf_queue fmt::fmt tuplet::tuplet swl-variant veque
        crypto asap hwinfo gamepad magic_enum::magic_enum self_macro stduuid v8pp)
add_dependencies(${PROJECT_NAME} modules)
foreach (QT_COMPONENT ${QT_COMPONENTS})
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::${QT_COMPONENT})
endforeach ()
