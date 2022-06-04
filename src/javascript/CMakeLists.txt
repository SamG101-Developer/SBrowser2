add_library(javascript INTERFACE)
add_subdirectory(web_apis)
set_target_properties(javascript PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(javascript INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
