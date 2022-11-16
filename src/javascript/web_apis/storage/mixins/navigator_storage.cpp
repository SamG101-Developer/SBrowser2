#include "navigator_storage.hpp"
#include "navigator_storage_private.hpp"


auto storage::mixins::navigator_storage::get_storage() const -> storage_manager*
{
    ACCESS_PIMPL(const navigator_storage);
    return d->storage.get();
}


auto storage::mixins::navigator_storage::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<navigator_storage>{isolate}
        .inherit<dom_object>()
        .property("storage", &navigator_storage::get_storage)
        .auto_wrap_objects();

    return std::move(conversion);
}
