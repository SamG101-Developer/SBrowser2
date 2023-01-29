module;
#include "ext/macros.hpp"


export module apis.storage.mixins.navigator_storage:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(storage::mixins, navigator_storage)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(navigator_storage);

public:
    std::unique_ptr<storage_manager> storage;
};
