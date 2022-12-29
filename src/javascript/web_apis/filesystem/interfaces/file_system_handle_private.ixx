module;
#include "ext/macros/pimpl.hpp"


export module apis.filesystem.file_system_handle_private;
import apis.dom_object_private;

import apis.filesystem.types;


DEFINE_PRIVATE_CLASS(filesystem, file_system_handle)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(file_system_handle);

public:
    std::shared_ptr<detail::entry_t> entry;
};
