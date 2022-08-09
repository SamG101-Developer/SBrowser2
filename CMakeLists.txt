cmake_minimum_required(VERSION 3.22)
project(SBrowser2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-backtrace-limit=0")
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

include_directories(src)
include_directories(src/javascript)
include_directories(src/javascript/web_apis)

file(GLOB_RECURSE FIRST_PARTY_SOURCE_FILES src/*.cpp)


include(FetchContent)

FetchContent_Declare(AssertReplacement
        GIT_REPOSITORY "https://github.com/jeremy-rifkin/libassert.git"
        GIT_TAG "origin/master")

FetchContent_Declare(CoroutineReplacement
        GIT_REPOSITORY "https://github.com/andreasbuhr/cppcoro.git"
        GIT_TAG "origin/main")

FetchContent_Declare(FilesystemReplacement
        GIT_REPOSITORY "https://github.com/cginternals/cppfs.git"
        GIT_TAG "origin/master")

FetchContent_Declare(FunctionReplacement
        GIT_REPOSITORY "https://github.com/Naios/function2.git"
        GIT_TAG "origin/master")

FetchContent_Declare(HashMapSetReplacement
        GIT_REPOSITORY "https://github.com/Tessil/robin-map.git"
        GIT_TAG "origin/master")

FetchContent_Declare(QueueReplacement
        GIT_REPOSITORY "https://github.com/cameron314/concurrentqueue.git"
        GIT_TAG "origin/master")

FetchContent_Declare(RandomReplacement
        GIT_REPOSITORY "https://github.com/effolkronium/random.git"
        GIT_TAG "origin/master")

FetchContent_Declare(RangeReplacement
        GIT_REPOSITORY "https://github.com/ericniebler/range-v3.git"
        GIT_TAG "origin/master")

FetchContent_Declare(RegexReplacement
        GIT_REPOSITORY "https://github.com/hanickadot/compile-time-regular-expressions.git"
        GIT_TAG "origin/main")

FetchContent_Declare(StackReplacement
        GIT_REPOSITORY "https://github.com/mattreecebentley/plf_stack.git"
        GIT_TAG "origin/master" CONFIGURE_COMMAND "" BUILD_COMMAND "")

FetchContent_Declare(StreamsReplacement
        GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
        GIT_TAG "origin/master")

FetchContent_Declare(ThreadReplacement
        GIT_REPOSITORY "https://github.com/bshoshany/thread-pool.git"
        GIT_TAG "origin/master")

FetchContent_Declare(TupleReplacement
        GIT_REPOSITORY "https://github.com/codeinred/tuplet.git"
        GIT_TAG "origin/main")

FetchContent_Declare(VariantReplacement
        GIT_REPOSITORY "https://github.com/groundswellaudio/swl-variant.git"
        GIT_TAG "origin/main")

FetchContent_Declare(VectorReplacement
        GIT_REPOSITORY "https://github.com/Shmoopty/veque.git"
        GIT_TAG "origin/master")

FetchContent_Declare(MagicEnum
        GIT_REPOSITORY "https://github.com/Neargye/magic_enum.git"
        GIT_TAG "origin/master")

FetchContent_Declare(UUIDs
        GIT_REPOSITORY "https://github.com/mariusbancila/stduuid.git"
        GIT_TAG "origin/master")

FetchContent_Declare(V8PP
        GIT_REPOSITORY "https://github.com/pmed/v8pp.git"
        GIT_TAG "origin/master")

add_executable(${PROJECT_NAME} main.cpp ${FIRST_PARTY_SOURCE_FILES})

file(COPY "${CMAKE_SOURCE_DIR}/third_party/v8-v143-x64.10.0.139.9" DESTINATION "${CMAKE_BINARY_DIR}/_deps/v8pp-build")
file(COPY "${CMAKE_SOURCE_DIR}/third_party/v8.redist-v143-x64.10.0.139.9" DESTINATION "${CMAKE_BINARY_DIR}/_deps/v8pp-build")


FetchContent_MakeAvailable(
        AssertReplacement CoroutineReplacement FilesystemReplacement FunctionReplacement HashMapSetReplacement
        QueueReplacement RandomReplacement RangeReplacement RegexReplacement StackReplacement StreamsReplacement
        ThreadReplacement TupleReplacement VariantReplacement VectorReplacement MagicEnum UUIDs V8PP)


add_library(plf_stack INTERFACE)
target_include_directories(plf_stack INTERFACE ${CMAKE_BINARY_DIR}/_deps/stackreplacement-src)

add_library(bs_thread_pool INTERFACE)
target_include_directories(bs_thread_pool INTERFACE ${CMAKE_BINARY_DIR}/_deps/threadreplacement-src)

add_library(veque INTERFACE)
target_include_directories(veque INTERFACE ${CMAKE_BINARY_DIR}/_deps/vectorreplacement-src/include)

target_link_libraries(${PROJECT_NAME}
        assert cppcoro cppfs function2::function2 tsl::robin_map concurrentqueue effolkronium_random range-v3::range-v3
        ctre::ctre plf_stack fmt::fmt bs_thread_pool tuplet::tuplet swl-variant veque magic_enum::magic_enum stduuid
        v8pp)
