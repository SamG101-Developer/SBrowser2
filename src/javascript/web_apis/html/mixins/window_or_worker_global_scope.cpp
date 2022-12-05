#include "window_or_worker_global_scope.hpp"
#include "window_or_worker_global_scope_private.hpp"

#include "javascript/environment/settings.ixx"


#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"

#include "html/detail/origin_internals.hpp"
#include "html/detail/worker_internals.hpp"

#include "url/detail/url_internals.hpp"

#include <range/v3/action/remove.hpp>
#include <range/v3/algorithm/any_of.hpp>


auto html::mixins::window_or_worker_global_scope::report_error(ext::any&& e) -> void
{
    detail::report_exception(std::move(e));
}


auto html::mixins::window_or_worker_global_scope::btoa(ext::string_view data) -> ext::string
{
    using enum dom::detail::dom_exception_error_t;
    dom::detail::throw_v8_exception<INVALID_CHARACTER_ERR>(
            [data]
            {
        return ranges::any_of(
                data,
                [](char8_t code_point) {return code_point > 0x00ff;});
            },
            u"Code point must be <= 0x00ff");

    return infra::detail::forgiving_base64_encode(data);
}


auto html::mixins::window_or_worker_global_scope::atob(ext::string_view data) -> ext::byte_string
{
    using enum dom::detail::dom_exception_error_t;
    auto decoded_data = infra::detail::forgiving_base64_decode(data);
    dom::detail::throw_v8_exception<INVALID_CHARACTER_ERR>(
            [decoded_data]
            {
        return ranges::any_of(
                decoded_data,
                [](char8_t code_point) {return code_point > 0x00ff;});
            },
            u"Code point must be <= 0x00ff");

    return decoded_data;
}


template <typename ...Args>
auto html::mixins::window_or_worker_global_scope::set_timeout(
        detail::timer_handler_t&& handler,
        ext::number<long> timeout,
        Args&&... arguments) -> ext::number<long>
{
    return detail::timer_initialization_steps(this, std::move(handler), timeout, std::forward<Args>(arguments)..., false);
}


template <typename ...Args>
auto html::mixins::window_or_worker_global_scope::set_interval(
        detail::timer_handler_t&& handler,
        ext::number<long> timeout,
        Args&& ...arguments)
        -> ext::number<long>
{
    return detail::timer_initialization_steps(this, std::move(handler), timeout, std::forward<Args>(arguments)..., true);
}


auto html::mixins::window_or_worker_global_scope::clear_timeout(ext::number<long> id) -> void
{
    ACCESS_PIMPL(window_or_worker_global_scope);
    d->active_timers |= ranges::actions::remove(id);
}


auto html::mixins::window_or_worker_global_scope::clear_interval(ext::number<long> id) -> void
{
    ACCESS_PIMPL(window_or_worker_global_scope);
    d->active_timers |= ranges::actions::remove(id);
}


auto html::mixins::window_or_worker_global_scope::queue_microtask(ext::function<void()>&& callback) -> void
{
    JS_EXCEPTION_HANDLER;
    dom::detail::queue_microtask(std::move(callback));
    if (JS_EXCEPTION_HAS_THROWN)
        detail::report_exception(JS_EXCEPTION);
}


auto html::mixins::window_or_worker_global_scope::get_origin() const -> ext::string
{
    auto e = js::env::env::relevant(this);
    return detail::serialize_origin(e.cpp.settings()->origin);
}


auto html::mixins::window_or_worker_global_scope::get_is_secure_context() const -> ext::boolean
{
    auto e = js::env::env::relevant(this);
    return e.cpp.settings()->is_secure_context;
}


auto html::mixins::window_or_worker_global_scope::get_cross_origin_isolated() const -> ext::boolean
{
    auto e = js::env::env::relevant(this);
    return e.cpp.settings()->cross_origin_isolated_capability;
}
