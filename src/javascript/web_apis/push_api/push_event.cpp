#include "push_event.hpp"
#include "push_event_private.hpp"

#include INCLUDE_INNER_TYPES(push_api)

#include "push_api/detail/push_internals.hpp"
#include "push_api/push_message_data.hpp"
#include "push_api/push_message_data_private.hpp"


push_api::push_event::push_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : service_workers::events::extendable_event(std::move(event_type), std::move(event_init))
{
    INIT_PIMPL(push_event);
    ACCESS_PIMPL(push_event);

    d->data = std::make_unique<push_message_data>();
    d->data->d_func()->bytes = detail::extract_byte_sequence(event_init[u8"data"].to<detail::byte_sequence_container_t>());
}


auto push_api::push_event::get_data() const -> push_message_data*
{
    ACCESS_PIMPL(const push_event);
    return d->data.get();
}
