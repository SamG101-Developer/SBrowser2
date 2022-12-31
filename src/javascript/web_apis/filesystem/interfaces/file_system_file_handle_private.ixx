module;
#include "ext/macros.hpp"


export module apis.filesystem.file_system_file_handle:p;
import apis.filesystem.file_system_handle;

IMPORT_ALL_TYPES(filesystem);


DEFINE_PRIVATE_CLASS(filesystem, file_system_file_handle)
        : filesystem::file_system_handle_private
{
public:
    MAKE_QIMPL(file_system_file_handle);

public:
    std::shared_ptr<detail::file_entry_t> entry;
};
