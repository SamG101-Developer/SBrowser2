#include "fetch_event.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "dom/detail/exception_internals.hpp"
#include "service_workers/detail/event_internals.hpp"


auto service_workers::events::fetch_event::respond_with(
        ext::promise<fetch::response*>&& r)
        -> void
{
    ACCESS_PIMPL(fetch_event);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [dispatched = d->dispatch_flag] {return !dispatched;},
            "Cannot respond to an event that hasn't already been dispatched");

    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [respond_with_entered = d->respond_with_entered_flag] {return respond_with_entered;},
            "Cannot response to an event that responds-with-entered");

    detail::add_lifetime_promise(std::move(r), this);
    d->stop_propagation_flag = true;
    d->stop_immediate_propagation_flag = true;
    d->respond_with_entered_flag = true;

    JS_REALM_GET_RELEVANT(this);
    r.rejection_steps = [d]
    {
        d->respond_with_error_flag = true;
        d->wait_to_response_flag = false;
    };

    r.fulfillment_steps = [d]
    {
        // TODO
    };
}


auto service_workers::events::fetch_event::get_request() const -> fetch::request*
{
    ACCESS_PIMPL(const fetch_event);
    return d->request.get();
}


auto service_workers::events::fetch_event::get_preload_response() const -> const ext::promise<ext::any>&
{
    ACCESS_PIMPL(const fetch_event);
    return d->preload_response;
}


auto service_workers::events::fetch_event::get_handled() const -> const ext::promise<void>&
{
    ACCESS_PIMPL(const fetch_event);
    return d->handled;
}


auto service_workers::events::fetch_event::get_client_id() const -> ext::string_view
{
    ACCESS_PIMPL(const fetch_event);
    return d->client_id;
}


auto service_workers::events::fetch_event::get_resulting_client_id() const -> ext::string_view
{
    ACCESS_PIMPL(const fetch_event);
    return d->resulting_client_id;
}


auto service_workers::events::fetch_event::get_replaces_client_id() const -> ext::string_view
{
    ACCESS_PIMPL(const fetch_event);
    return d->replaces_client_id;
}
