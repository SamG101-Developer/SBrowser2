#include "shared_worker_global_scope.hpp"
#include "shared_worker_global_scope_private.hpp"


auto html::workers::shared_worker_global_scope::get_name() const -> ext::string_view
{
    ACCESS_PIMPL(const shared_worker_global_scope);
    return d->name;
}
