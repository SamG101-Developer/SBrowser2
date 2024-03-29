module;
#include "ext/macros.hpp"


export module apis.filesystem.file_system_sync_access_handle;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(filesystem, file_system_sync_access_handle) final
        : virtual public dom_object
{
public typedefs:
    using file_system_read_write_options_t = ext::map<ext::string, ext::any>;

public constructors:
    file_system_sync_access_handle();
    MAKE_PIMPL(file_system_sync_access_handle);
    MAKE_V8_AVAILABLE(DEDICATED_WORKER | SECURE);

private js_methods:
    auto read(ext::buffer_source& buffer, file_system_read_write_options_t&& options = {}) -> ext::number<ulonglong>;
    auto write(ext::buffer_source& buffer, file_system_read_write_options_t&& options = {}) -> ext::number<ulonglong>;
    auto truncate(ext::number<ulonglong> new_size) -> void;

    auto get_size() const -> ext::number<ulonglong>;
    auto flush() -> void;
    auto close() const -> void;
};
