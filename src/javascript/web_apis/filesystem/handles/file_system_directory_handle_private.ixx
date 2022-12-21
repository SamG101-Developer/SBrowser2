module;
#include "ext/macros/pimpl.hpp"


export module apis.filesystem.file_system_directory_handle;
import apis.filesystem.file_system_handle_private;
import ext.mixins;

import apis.filesystem.tyes;
import ext.core;


DEFINE_PRIVATE_CLASS(filesystem, file_system_directory_handle)
        : filesystem::file_system_handle_private
        , ext::map_like_private<ext::string, file_system_handle*>
{
public:
    MAKE_QIMPL(file_system_directory_handle);

public:
    std::shared_ptr<detail::directory_entry_t> entry;
};
