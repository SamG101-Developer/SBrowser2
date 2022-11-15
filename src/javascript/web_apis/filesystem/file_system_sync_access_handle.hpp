#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_SYNC_ACCESS_HANDLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_SYNC_ACCESS_HANDLE_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace filesystem {class file_system_sync_access_handle;}
namespace filesystem {class file_system_sync_access_handle_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(filesystem)
#include "ext/array_buffer.hpp"


class filesystem::file_system_sync_access_handle
        : virtual public dom_object
{
public constructors:
    file_system_sync_access_handle();
    MAKE_PIMPL(file_system_sync_access_handle);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto read(ext::buffer_source& buffer, detail::file_system_read_write_options_t&& options = {}) -> ext::number<ulonglong>;
    auto write(ext::buffer_source& buffer, detail::file_system_read_write_options_t&& options = {}) -> ext::number<ulonglong>;
    auto truncate(ext::number<ulonglong> new_size) -> void;

    auto get_size() const -> ext::number<ulonglong>;
    auto flush() -> void;
    auto close() const -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_SYNC_ACCESS_HANDLE_HPP
