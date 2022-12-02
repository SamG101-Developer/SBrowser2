#include "media_capabilities.hpp"
#include "environment/realms.hpp"
#include "media_capabilities_private.hpp"

#include "ext/casting.ixx"

#include "dom/_typedefs.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/workers/worker_global_scope.hpp"
#include "media_capabilities/detail/configuration_internals.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"

#include <v8-exception.h>


auto media::capabilities::media_capabilities::decoding_info(
        detail::media_decoding_configuration_t&& configuration)
        -> ext::promise<detail::media_capabilities_decoding_info_t>
{
    auto e = js::env::env::current();
    using enum dom::detail::dom_exception_error_t;
    auto promise = ext::promise<detail::media_capabilities_decoding_info_t>{};

    if (!detail::is_valid_media_decoding_configuration(std::move(configuration)))
        return web_idl::detail::reject_promise(promise, e.js.realm(), v8::Exception::TypeError(v8pp::to_v8(e.js.agent(), "Invalid 'configuration'")));

    if (configuration.contains(u"keySystemConfiguration") && e.cpp.global<html::workers::worker_global_scope*>())
        return web_idl::detail::reject_promise(promise, e.js.realm(), dom::other::dom_exception{u8"Global object can not be a WorkerGlobalScope", INVALID_STATE_ERR});

    if (configuration.contains(u"keySystemConfiguration") && secure_contexts::detail::is_environment_settings_object_in_secure_context(current_settings_object))
        return web_idl::detail::reject_promise(promise, e.js.realm(), dom::other::dom_exception{u8"Global env settings must be in a secure context", SECURITY_ERR});;

    GO [&e, &promise, configuration = std::move(configuration)] mutable
    {
        web_idl::detail::resolve_promise(promise, e.js.realm(), detail::create_media_capabilities_decoding_info(std::move(configuration)));
    };

    return promise;
}


auto media::capabilities::media_capabilities::encoding_info(
        detail::media_encoding_configuration_t&& configuration)
        -> ext::promise<detail::media_capabilities_encoding_info_t>
{
    auto e = js::env::env::current();
    auto promise = ext::promise<detail::media_capabilities_decoding_info_t>{};

    if (!detail::is_valid_media_configuration(std::move(configuration)))
        return web_idl::detail::reject_promise(promise, e.js.realm(), v8::Exception::TypeError(v8pp::to_v8(e.js.agent(), "Invalid 'configuration'")));

    GO [&e, &promise, configuration = std::move(configuration)] mutable
    {
        web_idl::detail::resolve_promise(promise, e.js.realm(), detail::create_media_capabilities_encoding_info(std::move(configuration)));
    };

    return promise;
}


auto media::capabilities::media_capabilities::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<media_capabilities>{isolate}
        .inherit<dom_object>()
        .function("decodingInfo", &media_capabilities::decoding_info)
        .function("encodingInfo", &media_capabilities::encoding_info)
        .auto_wrap_objects();

    return std::move(conversion);
}
