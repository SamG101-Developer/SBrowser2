module;
#include "ext/macros/annotations.hpp"
#include "ext/macros.hpp"
#include "ext/macros/other.hpp"
#include "javascript/macros/expose.hpp"
#include <v8-forward.h>


export module apis.filesystem.file_system_directory_handle;
import apis.filesystem.file_system_handle;
import ext.mixins;

import apis.filesystem.types;
import ext.core;
import ext.js;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(filesystem, file_system_directory_handle) final
        : public filesystem::file_system_handle
        , public ext::async_map_like<ext::string, file_system_handle*>
{
public typedefs:
    using file_system_get_file_options_t = ext::map<ext::string, ext::boolean>;
    using file_system_get_directory_options_t = ext::map<ext::string, ext::boolean>;
    using file_system_remove_options_t = ext::map<ext::string, ext::boolean>;

public constructors:
    file_system_directory_handle();
    MAKE_PIMPL(file_system_directory_handle);
    MAKE_SERIALIZABLE;
    MAKE_V8_AVAILABLE(WINDOW | WORKER | SECURE);

public js_methods:
    auto get_file_handle(ext::string_view name, file_system_get_file_options_t&& options = {}) -> ext::promise<std::unique_ptr<file_system_file_handle>>;
    auto get_directory_handle(ext::string_view name, file_system_get_directory_options_t&& options = {}) -> ext::promise<std::unique_ptr<file_system_directory_handle>>;
    auto remove_entry(ext::string_view name, file_system_remove_options_t&& options = {}) -> ext::promise<void>;
    auto resolve(file_system_handle* possible_descendant) -> ext::promise<ext::vector<ext::string>>;
};
