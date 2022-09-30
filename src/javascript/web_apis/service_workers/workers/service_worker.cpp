#include "service_worker.hpp"

#include "url/detail/url_internals.hpp"


service_workers::workers::service_worker::service_worker()
{
    INIT_PIMPL(service_worker);
}


auto service_workers::workers::service_worker::post_message(
        ext::any&& message,
        ext::vector<ext::any>&& transfer) -> void
{
    post_message(std::move(message), html::detail::structured_serialize_options_t{{"transfer", std::move(transfer)}});
}


auto service_workers::workers::service_worker::post_message(
        ext::any&& message,
        html::detail::structured_serialize_options_t&& options)
        -> void
{
    JS_REALM_GET_INCUMBENT;
    // TODO
}


auto service_workers::workers::service_worker::get_script_url() const -> ext::string
{
    ACCESS_PIMPL(const service_worker);
    return url::detail::url_serializer(*d->script_url);
}


auto service_workers::workers::service_worker::get_state() const -> detail::service_worker_state_t
{
    ACCESS_PIMPL(const service_worker);
    return d->state;
}


auto service_workers::workers::service_worker::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    using _signature_post_message_0 = void(service_worker::*)(ext::any&&, ext::vector<ext::any>&&);
    using _signature_post_message_1 = void(service_worker::*)(ext::any&&, html::detail::structured_serialize_options_t&&);

    decltype(auto) conversion = v8pp::class_<service_worker>{isolate}
        .inherit<dom::nodes::event_target>()
        .function<_signature_post_message_0>("postMessage", &service_worker::post_message)
        .function<_signature_post_message_1>("postMessage", &service_worker::post_message)
        .property("scriptURL", &service_worker::get_script_url)
        .property("state", &service_worker::get_state)
        .auto_wrap_objects();

    return std::move(conversion);
}
