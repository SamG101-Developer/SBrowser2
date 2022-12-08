#include "merchant_validation_event.hpp"
#include "merchant_validation_event_private.hpp"






#include "payment_method_id/detail/identifier_internals.hpp"
#include "payment_request/payment_request.hpp"
#include "payment_request/payment_request_private.hpp"
#include "payment_request/payment_response.hpp"
#include "payment_request/payment_response_private.hpp"
#include "url/detail/url_internals.hpp"


merchant_validation::merchant_validation_event::merchant_validation_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
{
    auto e = js::env::env::relevant(this);
    decltype(auto) base_url = *e.cpp.settings()->api_base_url;
    decltype(auto) validation_url = url::detail::url_parser(event_init[u"validationURL"].to<ext::string>());

    using enum v8_primitive_error_t;
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&validation_url] {return !validation_url.has_value();},
            u8"Invalid validationURL", e);

    dom::detail::throw_v8_exception<V8_RANGE_ERROR>(
            [&event_init] {return event_init.contains(u"methodName") && payment::detail::validate_payment_method_identifier(event_init[u"methodName"].to<ext::string>());},
            u8"Invalid methodName", e);

    INIT_PIMPL(merchant_validation_event);
    ACCESS_PIMPL(merchant_validation_event);
    d->validation_url = std::move(*validation_url);
    d->method_name = std::move(event_init[u"methodName"].to<ext::string>());
    d->wait_for_update = false;
}


auto merchant_validation::merchant_validation_event::complete(
        ext::promise<ext::any>&& merchant_session_promise)
        -> void // TODO : Same as payment_request_update_event::update_with()
{
    ACCESS_PIMPL(merchant_validation_event);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return !d->is_trusted;},
            u8"Cannot complete a non-trusted event");

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->wait_for_update;},
            u8"Cannot complete an event that is waiting for an update");

    decltype(auto) request = dom_cast<payment::request::payment_response*>(d->target)
            ? dom_cast<payment::request::payment_response*>(d->target)->d_func()->request
            : dom_cast<payment::request::payment_request*>(d->target);
    ASSERT(request);

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [request] {return request->d_func()->state != payment::detail::state_t::INTERACTIVE;},
            u8"Target must be interactive");

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [request] {return request->d_func()->updating;},
            u8"Request cannot be updating");

    d->stop_propagation_flag = true;
    d->stop_immediate_propagation_flag = true;
    d->wait_for_update = true;

    detail::validate_merchant_details(std::move(merchant_session_promise), request);
}


auto merchant_validation::merchant_validation_event::get_method_name() const -> ext::string_view
{
    ACCESS_PIMPL(const merchant_validation_event);
    return d->method_name;
}


auto merchant_validation::merchant_validation_event::get_validation_url() const -> ext::string
{
    ACCESS_PIMPL(const merchant_validation_event);
    return url::detail::url_serializer(*d->validation_url);
}


auto merchant_validation::merchant_validation_event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::events::event>()
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .property("methodName", &merchant_validation_event::get_method_name)
        .property("validationURL", &merchant_validation_event::get_validation_url)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
