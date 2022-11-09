#include "navigator.hpp"
#include "navigator_private.hpp"

#include "ext/threading.hpp"

#include "javascript/environment/environment_settings.hpp"
#include "javascript/environment/realms.hpp"

#include "badging/_typedefs.hpp"
#include "battery/battery_manager.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/other/dom_exception.hpp"
#include "dom/other/dom_exception_private.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "hr_time/performance.hpp"
#include "hr_time/detail/time_internals.hpp"

#include "gamepad/gamepad.hpp"
#include "html/detail/document_internals.hpp"
#include "mediacapture_main/media_devices.hpp"

#include "url/detail/encoding_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/view/filter.hpp>


auto html::navigators::navigator::get_user_media(
        ext::map<ext::string, ext::any>&& constraints,
        navigator_user_media_success_callback_t&& success_callback,
        navigator_user_media_error_callback_t&& error_callback)
        const -> void
{
    ACCESS_PIMPL(const navigator);
    auto promise = d->media_devices->get_user_media(std::move(constraints));
    // TODO : call success_callback when ext::promise set-value called
    // TODO : call error callback when ext::promise set-error called
}


auto html::navigators::navigator::send_beacon(
        ext::string&& url,
        fetch::detail::body_init_t data)
        -> void
{
    auto e = js::env::env::relevant(this);
    decltype(auto) base   = e.cpp.settings()->api_base_url.get();
    decltype(auto) origin = e.cpp.settings()->origin;
    auto parsed_url = url::detail::url_parser(std::move(url), base);

    // TODO
}


auto html::navigators::navigator::set_client_badge(
        ext::optional<ext::number<ulonglong>> contents)
        -> ext::promise<void>
{
    // Run an algorithm in parallel that handles setting the badge of the Document.
    GO [this, &contents]
    {
        auto e = js::env::env::relevant(this);
        decltype(auto) document = e.cpp.global<dom::nodes::window*>()->d_func()->document.get();
        document->m_badge = !contents.has_value()
                ? badging::detail::badge_value_t::FLAG : *contents == 0
                ? badging::detail::badge_value_t::NOTHING : std::move(*contents);

        // TODO
    };

    // Return a resolved ext::promise<void> whilst the above code is executing in another thread.
    ext::promise<void> promise;
    promise.resolve();
    return promise;
}


auto html::navigators::navigator::clear_client_badge()
        -> ext::promise<void>
{
    GO [this]
    {
        auto e = js::env::env::relevant(this);
        decltype(auto) document = e.cpp.global<dom::nodes::window*>()->d_func()->document.get();
        document->m_badge = badging::detail::badge_value_t::NOTHING;
    };

    // Return a resolved ext::promise<void> whilst the above code is executing in another thread.
    ext::promise<void> promise;
    promise.resolve();
    return promise;
}


auto html::navigators::navigator::get_battery()
        -> ext::promise<battery::battery_manager*>&
{
    ACCESS_PIMPL(navigator);
    using enum dom::detail::dom_exception_error_t;

    // If the [[BatteryPromise]] slot is empty, then create a new slot, as the contents of the lost (promise) are
    // required for the rest of the method.
    d->battery_promise = d->battery_promise.value()
            ? d->battery_promise
            : ext::promise<battery::battery_manager*>{};

    // Get the associated document of the relevant global object, cast to a Document.
    auto e = js::env::env::relevant(this);
    decltype(auto) document = e.cpp.global<dom::nodes::window*>()->d_func()->document.get();

    // If the Document isn't allowed to use the Battery feature, then reject the [[BatteryPromise]] with a
    // NOT_ALLOWED_ERR, and return the contents of the [[BatteryManager]] slot.
    if (!html::detail::allowed_to_use(document, u"battery"))
    {
        d->battery_promise.reject(dom::other::dom_exception{u"Document is not allowed to use the Battery feature", NOT_ALLOWED_ERR});
        return d->battery_promise;
    }

    // Otherwise, fill the [[BatteryManager]] slot with a new BatteryManager object (will be deleted in the destructor
    // of the Navigator)
    else
    {
        d->battery_manager = d->battery_manager ?: new battery::battery_manager{};
        d->battery_promise.reject(d->battery_manager);
    }

    // Return the [[BatteryPromise]]
    return d->battery_promise;
}


auto html::navigators::navigator::get_gamepads()
        -> ext::vector_span<gamepad::gamepad*>
{
    ACCESS_PIMPL(navigator);
    using enum dom::detail::dom_exception_error_t;

    // Get the associated document of the relevant global object, cast to a Document.
    auto e = js::env::env::relevant(this);
    decltype(auto) document = e.cpp.global<dom::nodes::window*>()->d_func()->document.get();
    return_if (!document || !dom::detail::is_document_fully_active(document)) {};

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            BIND_FRONT(!html::detail::allowed_to_use, document, u"gamepad"),
            u8"Document is not allowed to use the 'gamepad' feature");

    return_if (!d->has_gamepad_gesture()) {};

    auto now = hr_time::detail::current_hr_time(e.js.global());
    auto valid_gamepad = [](gamepad::gamepad* gamepad) {return gamepad && !gamepad->d_func()->exposed;};

    for (auto* gamepad: d->gamepads | ranges::views::filter(std::move(valid_gamepad)))
    {
        gamepad->d_func()->exposed = true;
        gamepad->d_func()->timestamp = now;
    }

    return d->gamepads;
}
