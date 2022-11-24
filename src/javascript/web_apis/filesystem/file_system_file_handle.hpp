#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_FILE_HANDLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_FILE_HANDLE_HPP

// Inheritance Includes & This Class
#include "filesystem/file_system_handle.hpp"
namespace filesystem {class file_system_file_handle;}
namespace filesystem {class file_system_file_handle_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(filesystem)
namespace file_api {class file;}
namespace filesystem {class file_system_writable_file_stream;}
namespace filesystem {class file_system_sync_access_handle;}


class filesystem::file_system_file_handle
        : public filesystem::file_system_handle
{
public constructors:
    file_system_file_handle();
    MAKE_PIMPL(file_system_file_handle);
    MAKE_V8_AVAILABLE(WINDOW | WORKER | SECURE);

public js_methods:
    auto get_file() -> ext::promise<std::unique_ptr<file_api::file>>;
    auto create_writable(detail::file_system_create_writable_options_t&& options = {}) -> ext::promise<std::unique_ptr<file_system_writable_file_stream>>;
    auto create_sync_access_handle() -> ext::promise<std::unique_ptr<file_system_sync_access_handle>>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_FILE_HANDLE_HPP
