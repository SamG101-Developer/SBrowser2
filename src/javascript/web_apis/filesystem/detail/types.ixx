module;
#include "ext/macros/macros.hpp"
#include <function2/function2.hpp>
#include <swl/variant.hpp>


export module apis.filesystem.types;

import apis.permissions.types;
import apis.file_api.types;
import ext.core;
import ext.js;


DEFINE_FWD_DECL_NAMESPACE(filesystem)
{
    class file_system_directory_handle;
    class file_system_file_handle;
    class file_system_handle;
    class file_system_sync_access_handle;
    class file_system_writeable_file_stream;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(filesystem)
{
    struct entry_t;
    struct file_entry_t;
    struct directory_entry_t;

    enum class mode_t {READ, READWRITE};
    enum class lock_t {OPEN, TAKEN_EXCLUSIVE, TAKEN_SHARED};
    enum class take_lock_t {EXCLUSIVE, SHARED};
    enum class file_system_handle_kind_t {FILE, DIRECTORY};
    enum class write_command_type_t {WRITE, SEEK, TRUNCATE};
    enum class file_state_t {OPEN, CLOSED};
}


struct filesystem::detail::entry_t
{
    ext::string name;
    ext::function<permissions::detail::permission_state_t(mode_t)> query_access   = [](mode_t) {return permissions::detail::permission_state_t::DENIED;};
    ext::function<permissions::detail::permission_state_t(mode_t)> request_access = [](mode_t) {return permissions::detail::permission_state_t::DENIED;};

    auto operator==(const entry_t&) const -> ext::boolean;
    virtual ~entry_t();
};


struct filesystem::detail::file_entry_t : entry_t
{
    ext::u8string binary_data;
    ext::number<double> modification_timestamp;
    lock_t lock;
    ext::number<int> shared_lock_count;
};


struct filesystem::detail::directory_entry_t : entry_t
{
    ext::set<std::shared_ptr<entry_t>> children;
    std::observer_ptr<entry_t> parent;
};
