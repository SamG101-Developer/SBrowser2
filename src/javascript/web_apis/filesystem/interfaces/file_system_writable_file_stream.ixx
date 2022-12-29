module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"


export module apis.filesystem.file_system_writable_file_stream;
import apis.streams.writeable_stream;

import apis.file_api.types;
import apis.filesystem.types;
import ext.core;
import ext.js;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(filesystem, file_system_writable_file_stream) final
        : public streams::writable_stream
{
public typedefs:
    using write_params_t = ext::map<ext::string, ext::any>;
    using file_system_write_chunk_type_t = ext::variant<ext::buffer_source*, file_api::blob*, ext::string, write_params_t>;

public constructors:
    file_system_writable_file_stream();
    MAKE_PIMPL(file_system_writable_file_stream);
    MAKE_V8_AVAILABLE(WINDOW | WORKER | SECURE);

public js_methods:
    auto write(file_system_write_chunk_type_t&& data) -> ext::promise<void>;
    auto seek(ext::number<ulonglong> position) -> ext::promise<void>;
    auto truncate(ext::number<ulonglong> size) -> ext::promise<void>;
};
