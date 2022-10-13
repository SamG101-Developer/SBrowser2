#include "push_subscription.hpp"
#include "push_subscription_private.hpp"

#include "url/detail/url_internals.hpp"


auto push_api::push_subscription::get_endpoint() const -> ext::string
{
    ACCESS_PIMPL(const push_subscription);
    return url::detail::url_serializer(*d->push_endpoint);
}


auto push_api::push_subscription::get_expiration_time() const -> hr_time::epoch_time_stamp
{
    ACCESS_PIMPL(const push_subscription);
    return d->subscription_expiration_time;
}


auto push_api::push_subscription::get_options() const -> ext::map_span<ext::string, ext::any>
{
    ACCESS_PIMPL(const push_subscription);
    return d->options;
}
