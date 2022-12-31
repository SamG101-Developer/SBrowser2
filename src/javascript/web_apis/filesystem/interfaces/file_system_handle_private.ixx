module;
#include "ext/macros.hpp"


export module apis.filesystem.file_system_handle:p;
import apis.dom_object;

IMPORT_ALL_TYPES(filesystem);


DEFINE_PRIVATE_CLASS(filesystem, file_system_handle)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(file_system_handle);

public:
    std::shared_ptr<detail::entry_t> entry;
};
