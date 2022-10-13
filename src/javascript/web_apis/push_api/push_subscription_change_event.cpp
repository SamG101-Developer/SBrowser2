#include "push_subscription_change_event.hpp"
#include "push_subscription_change_event_private.hpp"

#include "push_api/push_subscription.hpp"


push_api::push_subscription_change_event::push_subscription_change_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : service_workers::events::extendable_event(std::move(event_type), std::move(event_init))
{
    INIT_PIMPL(push_subscription_change_event);

    ACCESS_PIMPL(push_subscription_change_event);
    d->old_subscription = std::unique_ptr<push_subscription>{event_init[u8"oldSubscription"].to<push_subscription*>()};
    d->new_subscription = std::unique_ptr<push_subscription>{event_init[u8"newSubscription"].to<push_subscription*>()};
}
