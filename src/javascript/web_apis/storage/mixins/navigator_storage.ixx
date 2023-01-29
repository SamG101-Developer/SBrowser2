module;
#include "ext/macros.hpp"


export module apis.storage.mixins.navigator_storage;


DEFINE_PUBLIC_CLASS(storage::mixins, navigator_storage)
        : public virtual dom_object
{
public constructors:
    navigator_storage();
    MAKE_PIMPL(navigator_storage);
    MAKE_V8_AVAILABLE(SECURE, ALL);

private js_properties:
    DEFINE_GETTER(storage, storage_manager*);
};
