#include "client.hpp"
#include "client_private.hpp"

#include "service_workers/workers/service_worker.hpp"
#include "service_workers/detail/client_internals.hpp"


auto service_workers::clients::client::get_frame_type() const -> detail::frame_type_t
{
    ACCESS_PIMPL(const client);
    return d->frame_type;
}
