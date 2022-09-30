#include "navigator.hpp"

#include "environment/environment_settings.hpp"
#include "ext/threading.hpp"
#include "javascript/environment/realms_2.hpp"

#include "battery/battery_manager.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/other/dom_exception.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/window.hpp"

#include "gamepad/gamepad.hpp"

#include "hr_time/performance.hpp"

#include "html/detail/document_internals.hpp"

#include "mediacapture_main/media_devices.hpp"

#include "url/detail/encoding_internals.hpp"
#include "url/detail/url_internals.hpp"
#include "v8pp/convert.hpp"

#include <range/v3/view/filter.hpp>

#include INCLUDE_INNER_TYPES(badging)
#include INCLUDE_INNER_TYPES(dom)


auto html::other::navigator::get_user_media(
        ext::map<ext::string, ext::any>&& constraints,
        html::other::navigator::navigator_user_media_success_callback&& success_callback,
        html::other::navigator::navigator_user_media_error_callback&& error_callback)
const -> void
{
    auto promise = media_devices()->get_user_media(std::move(constraints));
    // TODO : call success_callback when ext::promise set-value called
    // TODO : call error callback when ext::promise set-error called
}


auto html::other::navigator::send_beacon(
        ext::string&& url,
        fetch::detail::body_init_t data)
        -> void
{
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) base   = v8pp::from_v8<javascript::environment::settings_t*>(this_relevant_agent, this_relevant_global_object)->api_base_url.get();
    decltype(auto) origin = v8pp::from_v8<javascript::environment::settings_t*>(this_relevant_agent, this_relevant_global_object)->origin;

    auto parsed_url = url::detail::url_parser(std::move(url), base);

}


auto html::other::navigator::set_client_badge(
        ext::optional<ext::number<ulonglong>> contents)
        -> ext::promise<void>
{
    // Run an algorithm in parallel that handles setting the badge of the Document.
    GO [this, &contents]
    {
        JS_REALM_GET_RELEVANT(this);
        auto* document = javascript::environment::realms::get<dom::nodes::document*>(this_relevant_global_object, "responsible_document");
        document->m_badge = !contents.has_value()
                ? badging::detail::badge_value_t::FLAG : *contents == 0
                ? badging::detail::badge_value_t::NOTHING : std::move(*contents);
    };

    // Return a resolved ext::promise<void> whilst the above code is executing in another thread.
    ext::promise<void> promise;
    promise.set_value();
    return promise;
}


auto html::other::navigator::clear_client_badge()
        -> ext::promise<void>
{
    GO [this]
    {
        JS_REALM_GET_RELEVANT(this);
        auto* document = javascript::environment::realms::get<dom::nodes::document*>(this_relevant_global_object, "responsible_document");
        document->m_badge = badging::detail::badge_value_t::NOTHING;
    };

    // Return a resolved ext::promise<void> whilst the above code is executing in another thread.
    ext::promise<void> promise;
    promise.set_value();
    return promise;
}


auto html::other::navigator::get_battery()
        -> ext::promise<battery::battery_manager*>&
{
    // If the [[BatteryPromise]] slot is empty, then create a new slot, as the contents of the lost (promise) are
    // required for the rest of the method.
    s_battery_promise = s_battery_promise().get_future().get()
            ? s_battery_promise()
            : ext::promise<battery::battery_manager*>{};

    // Get the associated document of the relevant global object, cast to a Document.
    JS_REALM_GET_RELEVANT(this);
    auto* document = javascript::environment::realms::get<dom::nodes::document*>(this_relevant_global_object, "associated_document");

    // If the Document isn't allowed to use the Battery feature, then reject the [[BatteryPromise]] with a
    // NOT_ALLOWED_ERR, and return the contents of the [[BatteryManager]] slot.
    if (!html::detail::allowed_to_use(document, "battery"))
    {
        s_battery_promise().set_exception(dom::other::dom_exception{"Document is not allowed to use the Battery feature", NOT_ALLOWED_ERR});
        return s_battery_promise();
    }

    // Otherwise, fill the [[BatteryManager]] slot with a new BatteryManager object (will be deleted in the destructor
    // of the Navigator)
    else
    {
        s_battery_manager = s_battery_manager() ?: new battery::battery_manager{};
        s_battery_promise().set_value(s_battery_manager());
    }

    // Return the [[BatteryPromise]]
    return s_battery_promise();
}


auto html::other::navigator::get_gamepads()
        -> ext::vector<gamepad::gamepad*>&
{
    // Get the associated document of the relevant global object, cast to a Document.
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) document = v8pp::from_v8<dom::nodes::window*>(this_relevant_agent, this_relevant_global_object)->document();
    return_if (!document || !dom::detail::is_document_fully_active(document)) {};

    dom::detail::throw_v8_exception_formatted<SECURITY_ERR>(
            [document] {return !html::detail::allowed_to_use(document, "gamepad");},
            "Document is not allowed to use the 'gamepad' feature");

    return_if (!s_has_gamepad_gesture()) {};

    auto now = hr_time::detail::current_hr_time(this_relevant_global_object);
    auto valid_gamepad = [](gamepad::gamepad* gamepad) {return gamepad && !gamepad->s_exposed();};

    for (auto* gamepad: s_gamepads() | ranges::views::filter(std::move(valid_gamepad)))
    {
        gamepad->s_exposed = true;
        gamepad->s_timestamp = now;
    }

    return s_gamepads();
}
