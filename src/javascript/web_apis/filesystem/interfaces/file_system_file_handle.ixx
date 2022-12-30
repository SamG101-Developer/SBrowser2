module;
#include "ext/macros/annotations.hpp"
#include "ext/macros.hpp"

export module apis.filesystem.file_system_file_handle;
import apis.filesystem.file_system_handle;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(filesystem, file_system_file_handle) final
        : public filesystem::file_system_handle
{
public typedefs:
    using file_system_create_writable_options_t = ext::map<ext::string, ext::boolean>;

public constructors:
    file_system_file_handle();
    MAKE_PIMPL(file_system_file_handle);
    MAKE_V8_AVAILABLE(WINDOW | WORKER | SECURE);

public js_methods:
    auto get_file() -> ext::promise<std::unique_ptr<file_api::file>>;
    auto create_writable(file_system_create_writable_options_t&& options = {}) -> ext::promise<std::unique_ptr<file_system_writable_file_stream>>;
    auto create_sync_access_handle() -> ext::promise<std::unique_ptr<file_system_sync_access_handle>>;
};
