module;
#include "ext/macros/macros.hpp"


export module apis.filesystem.file_system_file_handle_private;
import apis.filesystem.file_system_handle_private;
import apis.filesystem.types;


DEFINE_PRIVATE_CLASS(filesystem, file_system_file_handle)
        : filesystem::file_system_handle_private
{
public:
    MAKE_QIMPL(file_system_file_handle);

public:
    std::shared_ptr<detail::file_entry_t> entry;
};
