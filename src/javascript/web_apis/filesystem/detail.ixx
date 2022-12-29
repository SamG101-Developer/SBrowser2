module;
#include "ext/macros/pimpl.hpp"


export module apis.filesystem.detail;
import apis.filesystem.types;

import ext.core;
import ext.js;
import js.env.realms;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(filesystem)
{
    auto is_valid_file_name(ext::string_view string) -> ext::boolean;
    auto take_lock(take_lock_t value, file_entry_t& file) -> ext::boolean;
    auto release_lock(file_entry_t& file) -> void;
    auto resolve_entry(entry_t& child, directory_entry_t& root) -> ext::promise<ext::vector<ext::string>>;
    auto create_filesystem_writable_stream(entry_t& entry, const js::env::env& e) -> std::unique_ptr<filesystem::file_system_writeable_file_stream>;
}
