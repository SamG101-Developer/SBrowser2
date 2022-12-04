#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_WRITABLE_FILE_STREAM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_WRITABLE_FILE_STREAM_HPP

// Inheritance Includes & This Class
#include "streams/writable/writable_stream.hpp"
namespace filesystem {class file_system_writable_file_stream;}
namespace filesystem {class file_system_writable_file_stream_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(filesystem)
#include "ext/promise.ixx"


class filesystem::file_system_writable_file_stream
        : public streams::writable::writable_stream
{
public constructors:
    file_system_writable_file_stream();
    MAKE_PIMPL(file_system_writable_file_stream);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto write(detail::file_system_write_chunk_type_t&& data) -> ext::promise<void>;
    auto seek(ext::number<ulonglong> position) -> ext::promise<void>;
    auto truncate(ext::number<ulonglong> size) -> ext::promise<void>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_WRITABLE_FILE_STREAM_HPP
