#include "credentials_container.hpp"

#include "javascript/environment/environment_settings.hpp"

#include "dom/abort/abort_signal.hpp"
#include "webappsec_credential_management/detail/algorithm_internals.hpp"


auto webappsec::credential_management::credentials_container::get(
        detail::credential_request_options_t&& options)
        -> ext::promise<credential*>
{
    JS_REALM_GET_CURRENT;
    // TODO : assert settings is in a secure context
    auto promise = ext::promise<credential*>{};

    decltype(auto) abort_signal = options.try_emplace("signal", nullptr).first->second.to<dom::abort::abort_signal*>();
    return_if (abort_signal->aborted()) promise.reject(abort_signal->reason());
    // TODO: mediation

    decltype(auto) settings_object = v8pp::from_v8<javascript::environment::settings_t*>(current_agent, current_settings_object);
    decltype(auto) origin = settings_object->origin;
    decltype(auto) same_origin_with_ancestors = detail::same_origin_with_ancestors(settings_object);
}
