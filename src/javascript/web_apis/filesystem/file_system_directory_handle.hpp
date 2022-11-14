#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_DIRECTORY_HANDLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_DIRECTORY_HANDLE_HPP

// Inheritance Includes & This Class
#include "filesystem/file_system_handle.hpp"
#include "ext/map_like.hpp"
namespace filesystem {class file_system_directory_handle;}
namespace filesystem {class file_system_directory_handle_private;}

// Other Includes & Forward Declarations
#include INCLUDE_CONCEPTS(html)
namespace filesystem {class file_system_file_handle;}


class filesystem::file_system_directory_handle
        : public filesystem::file_system_handle
        , public ext::map_like<ext::string, file_system_handle*> // TODO : async
{
public constructors:
    file_system_directory_handle();
    MAKE_PIMPL(file_system_directory_handle);
    MAKE_SERIALIZABLE;
    MAKE_V8_AVAILABLE;

public js_methods:
    auto get_file_handle(ext::string_view name, detail::file_system_get_file_options_t&& options = {}) -> ext::promise<file_system_file_handle>;
    auto get_directory_handle(ext::string_view name, detail::file_system_get_directory_options_t&& options = {}) -> ext::promise<file_system_directory_handle>;
    auto remove_entry(ext::string_view name, detail::file_system_remove_options_t&& options = {}) -> ext::promise<void>;
    auto resolve(file_system_handle* possible_descendant) -> ext::promise<ext::vector<ext::string>>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_DIRECTORY_HANDLE_HPP
