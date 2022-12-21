module;
#include "ext/macros/pimpl.hpp"


export module apis.filesystem.file_system_directory_handle;
import apis.filesystem.file_system_handle_private;


DEFINE_PRIVATE_CLASS(filesystem, file_system_directory_handle)
        : filesystem::file_system_handle_private
        , ext::map_like_private<ext::string, file_system_handle*>
{
    MAKE_QIMPL(file_system_directory_handle);
    std::shared_ptr<detail::directory_entry_t> entry;
};
