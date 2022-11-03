cmake_minimum_required(VERSION 3.22)
project(SBrowser2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-backtrace-limit=0") #-std=c++latest -Wno-dev -DCRYPTOPP_DISABLE_ASM")

set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

set(QT_VER 6.3.1)
set(QT_COMPONENTS Core Widgets Gui Multimedia MultimediaWidgets)

include_directories(src)
include_directories(src/javascript)
include_directories(src/javascript/web_apis)

file(GLOB_RECURSE FIRST_PARTY_SOURCE_FILES src/*.cpp)

include(FetchContent)
set(FETCH_CONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/_deps)

FetchContent_Declare(AssertReplacement
        GIT_REPOSITORY https://github.com/jeremy-rifkin/libassert.git
        GIT_TAG master)

FetchContent_Declare(ExpectedReplacement
        GIT_REPOSITORY https://github.com/TartanLlama/expected.git
        GIT_TAG master)

FetchContent_Declare(FunctionReplacement
        GIT_REPOSITORY https://github.com/Naios/function2.git
        GIT_TAG master)

FetchContent_Declare(HashMapSetReplacement
        GIT_REPOSITORY https://github.com/martinus/unordered_dense.git
        GIT_TAG main)

FetchContent_Declare(JsonReplacement
        GIT_REPOSITORY https://github.com/wqking/jsonpp.git
        GIT_TAG master)

FetchContent_Declare(OptionalReplacement
        GIT_REPOSITORY https://github.com/TartanLlama/optional.git
        GIT_TAG master)

FetchContent_Declare(QueueReplacement SOURCE_DIR ${FETCH_CONTENT_BASE_DIR}/queuereplacement-src/plf
        GIT_REPOSITORY https://github.com/mattreecebentley/plf_queue.git
        GIT_TAG main)

FetchContent_Declare(RandomReplacement
        GIT_REPOSITORY https://github.com/effolkronium/random.git
        GIT_TAG master)

FetchContent_Declare(RangeReplacement
        GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
        GIT_TAG master)

FetchContent_Declare(RegexReplacement # TODO : switch to Hyper...1
        GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions.git
        GIT_TAG main)

FetchContent_Declare(StackReplacement SOURCE_DIR ${FETCH_CONTENT_BASE_DIR}/stackreplacement-src/plf
        GIT_REPOSITORY https://github.com/mattreecebentley/plf_stack.git
        GIT_TAG master)

FetchContent_Declare(StreamsReplacement
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master)

FetchContent_Declare(TupleReplacement
        GIT_REPOSITORY https://github.com/codeinred/tuplet.git
        GIT_TAG main)

FetchContent_Declare(VariantReplacement
        GIT_REPOSITORY https://github.com/groundswellaudio/swl-variant.git
        GIT_TAG main)

FetchContent_Declare(VectorReplacement SOURCE_DIR ${FETCH_CONTENT_BASE_DIR}/vectorreplacement-src/veque
        GIT_REPOSITORY https://github.com/Shmoopty/veque.git
        GIT_TAG master)

FetchContent_Declare(HardwareInfo
        GIT_REPOSITORY https://github.com/lfreist/hwinfo.git
        GIT_TAG main)

FetchContent_Declare(Crypto SOURCE_DIR ${FETCH_CONTENT_BASE_DIR}/crypto-src/cryptopp
        GIT_REPOSITORY https://github.com/weidai11/cryptopp.git
        GIT_TAG master)

FetchContent_Declare(DateTime
        GIT_REPOSITORY https://github.com/mobius3/asap.git
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
        AssertReplacement ExpectedReplacement FunctionReplacement HashMapSetReplacement JsonReplacement
        OptionalReplacement QueueReplacement RandomReplacement RangeReplacement RegexReplacement StackReplacement
        StreamsReplacement TupleReplacement VariantReplacement VectorReplacement HardwareInfo Crypto DateTime
        MagicEnum SelfMacro UUIDs V8PP) # TODO : Qt

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/${QT_VER}/msvc2019_64")
find_package(Qt6 REQUIRED COMPONENTS ${QT_COMPONENTS})

add_executable(${PROJECT_NAME} main.cpp ${FIRST_PARTY_SOURCE_FILES})

file(COPY "${CMAKE_SOURCE_DIR}/third_party/v8-v143-x64.10.0.139.9" DESTINATION "${FETCH_CONTENT_BASE_DIR}/v8pp-build")
file(COPY "${CMAKE_SOURCE_DIR}/third_party/v8.redist-v143-x64.10.0.139.9" DESTINATION "${FETCH_CONTENT_BASE_DIR}/v8pp-build")
file(GLOB cryptopp_src ${FETCH_CONTENT_BASE_DIR}/crypto-src/cryptopp/*.cpp)


add_library(plf_stack INTERFACE)
target_include_directories(plf_stack INTERFACE ${FETCH_CONTENT_BASE_DIR}/stackreplacement-src)

add_library(plf_queue INTERFACE)
target_include_directories(plf_queue INTERFACE ${FETCH_CONTENT_BASE_DIR}/queuereplacement-src)

add_library(veque INTERFACE)
target_include_directories(veque INTERFACE ${FETCH_CONTENT_BASE_DIR}/vectorreplacement-src/veque/include)

add_library(crypto ${cryptopp_src})
target_include_directories(crypto PUBLIC ${FETCH_CONTENT_BASE_DIR}/crypto-src)

add_library(hwinfo INTERFACE)
target_include_directories(hwinfo INTERFACE ${FETCH_CONTENT_BASE_DIR}/hardwareinfo-src/include)

target_link_libraries(${PROJECT_NAME}
        assert expected function2::function2 unordered_dense::unordered_dense jsonpp optional effolkronium_random
        range-v3::range-v3 ctre::ctre plf_stack plf_queue fmt::fmt tuplet::tuplet swl-variant veque hwinfo crypto asap
        magic_enum::magic_enum self_macro stduuid v8pp)
foreach (QT_COMPONENT ${QT_COMPONENTS})
    target_link_libraries(${PROJECT_NAME} Qt6::${QT_COMPONENT})
endforeach ()
