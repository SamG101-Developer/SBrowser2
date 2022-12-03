#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_WRITABLE_FILE_STREAM_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_WRITABLE_FILE_STREAM_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "streams/writable/writable_stream_private.hpp"

#include INCLUDE_INNER_TYPES(filesystem)


DEFINE_PRIVATE_CLASS(filesystem, file_system_writable_file_stream) : streams::writable::writable_stream_private
{
    std::unique_ptr<detail::file_entry_t> file;
    ext::u8string byte_sequence;
    ext::number<int> seek_offset;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_WRITABLE_FILE_STREAM_PRIVATE_HPP
