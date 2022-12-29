module;
#include "ext/macros/macros.hpp"


export module apis.filesystem.file_system_writable_file_stream_private;
import apis.streams.writeable_stream_private;

import apis.filesystem.types;
import ext.core;


DEFINE_PRIVATE_CLASS(filesystem, file_system_writable_file_stream)
        : streams::writable_stream_private
{
public:
    MAKE_QIMPL(file_system_writable_file_stream);

public:
    std::unique_ptr<detail::file_entry_t> file;
    ext::u8string byte_sequence;
    ext::number<int> seek_offset;
};
