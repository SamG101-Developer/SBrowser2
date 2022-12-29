#include "worker_global_scope.hpp"
#include "worker_global_scope_private.hpp"


auto html::workers::worker_global_scope::get_self() const -> worker_global_scope*
{
    return this;
}


auto html::workers::worker_global_scope::get_location() const -> worker_location*
{
    ACCESS_PIMPL(const worker_global_scope);
    return d->location.get();
}


auto html::workers::worker_global_scope::get_navigator() const -> worker_navigator*
{
    ACCESS_PIMPL(const worker_global_scope);
    return d->worker_navigation.get();
}
