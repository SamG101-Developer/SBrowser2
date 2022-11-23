#include "body.hpp"
#include "body_private.hpp"

#include "fetch/detail/body_internals.hpp"
#include "streams/detail/readable_abstract_operations_internals.hpp"


auto fetch::mixins::body::get_body() const -> streams::readable::readable_stream*
{
    ACCESS_PIMPL(const body);
    return d->body ? d->body->stream.get() : nullptr;
}


auto fetch::mixins::body::get_body_used() const -> ext::boolean
{
    ACCESS_PIMPL(const body);
    return d->body && streams::detail::is_disturbed(d->body->stream.get());
}
