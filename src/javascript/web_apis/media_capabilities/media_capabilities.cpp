#include "media_capabilities.hpp"

#include USE_INNER_TYPES(dom)

#include "dom/other/dom_exception.hpp"
#include "html/workers/worker_global_scope.hpp"
#include "media_capabilities/detail/configuration_internals.hpp"

#include <v8-exception.h>


auto media::capabilities::media_capabilities::decoding_info(
        detail::media_decoding_configuration_t&& configuration)
        -> ext::promise<detail::media_capabilities_decoding_info_t>
{
    JS_REALM_GET_CURRENT;
    auto promise = ext::promise<detail::media_capabilities_decoding_info_t>{};

    if (!detail::is_valid_media_decoding_configuration(std::move(configuration)))
        return promise.reject(v8::Exception::TypeError(v8pp::to_v8(current_agent, "Invalid 'configuration'")));

    if (configuration.contains("keySystemConfiguration") && v8pp::from_v8<html::workers::worker_global_scope*>(current_agent, current_global_object))
        return promise.reject(dom::other::dom_exception{"Global object can not be a WorkerGlobalScope", INVALID_STATE_ERR});

    if (configuration.contains("keySystemConfiguration") && secure_contexts::detail::is_environment_settings_object_in_secure_context(current_settings_object))
        return promise.reject(dom::other::dom_exception{"Global environment settings must be in a secure context", SECURITY_ERR});;

    go [&promise, configuration = std::move(configuration)] mutable
    {promise.resolve(detail::create_media_capabilities_decoding_info(std::move(configuration)));};

    return promise;
}
