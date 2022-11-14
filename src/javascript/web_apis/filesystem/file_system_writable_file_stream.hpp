#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_WRITABLE_FILE_STREAM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_WRITABLE_FILE_STREAM_HPP

// Inheritance Includes & This Class
#include "streams/writable/writable_stream.hpp"
namespace filesystem {class file_system_writable_file_stream;}
namespace filesystem {class file_system_writable_file_stream_private;}

// Other Includes & Forward Declarations


class filesystem::file_system_writable_file_stream
        : public streams::writable::writable_stream
{
public constructors:
    file_system_writable_file_stream();
    MAKE_PIMPL(file_system_writable_file_stream);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_WRITABLE_FILE_STREAM_HPP
