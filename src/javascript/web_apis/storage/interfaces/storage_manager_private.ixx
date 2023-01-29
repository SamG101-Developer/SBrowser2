module;
#include "ext/macros.hpp"


export module apis.storage.storage_manager:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(storage, storage_manager)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(storage_manager);
};
