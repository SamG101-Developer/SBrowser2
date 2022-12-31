module;
#include "ext/macros.hpp"


export module apis.filesystem.file_system_sync_access_handle:p;
import apis.dom_object;

IMPORT_ALL_TYPES(filesystem);


DEFINE_PRIVATE_CLASS(filesystem, file_system_sync_access_handle) : dom_object_private
{
public:
    MAKE_QIMPL(file_system_sync_access_handle);

public:
    std::unique_ptr<detail::file_entry_t> file;
    detail::file_state_t state;
};
