module;
#include "ext/macros.hpp"


module apis.storage.mixins.navigator_storage;


auto storage::mixins::navigator_storage::get_storage() const -> storage_manager*
{
    ACCESS_PIMPL;
    return d->storage.get();
}
