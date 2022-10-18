#include "window_or_worker_global_scope.hpp"
#include "window_or_worker_global_scope_private.hpp"

#include "javascript/environment/environment_settings.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "html/detail/origin_internals.hpp"

#include "url/detail/url_internals.hpp"

#include <range/v3/algorithm/any_of.hpp>


auto html::mixins::window_or_worker_global_scope::report_error(ext::any&& e) -> void
{
    detail::report_exception(std::move(e));
}


auto html::mixins::window_or_worker_global_scope::btoa(ext::string_view data) -> ext::string
{
    using enum dom::detail::dom_exception_error_t;
    dom::detail::throw_v8_exception_formatted<INVALID_CHARACTER_ERR>(
            [data] {ranges::any_of(data, BIND_BACK(ext::cmp::ge{}, 30, ext::identity{}));},
            "");
}


auto html::mixins::window_or_worker_global_scope::get_origin() const -> ext::string
{
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) settings = v8pp::from_v8<javascript::environment::settings_t*>(this_relevant_agent, this_relevant_settings_object);
    return detail::serialize_origin(settings->origin);
}


auto html::mixins::window_or_worker_global_scope::get_is_secure_context() const -> ext::boolean
{
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) settings = v8pp::from_v8<javascript::environment::settings_t*>(this_relevant_agent, this_relevant_settings_object);
    return settings->is_secure_context;
}


auto html::mixins::window_or_worker_global_scope::get_cross_origin_isolated() const -> ext::boolean
{
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) settings = v8pp::from_v8<javascript::environment::settings_t*>(this_relevant_agent, this_relevant_settings_object);
    return settings->cross_origin_isolated_capability;
}
