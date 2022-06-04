add_library(web_apis INTERFACE)
set_target_properties(web_apis PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(web_apis INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
