#include "dedicated_worker_global_scope.hpp"
#include "dedicated_worker_global_scope_private.hpp"


auto html::workers::dedicated_worker_global_scope::get_name() const -> ext::string_view
{
    ACCESS_PIMPL(const dedicated_worker_global_scope);
    return d->name;
}
