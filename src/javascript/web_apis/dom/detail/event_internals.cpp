#include "event_internals.hpp"

#include "ext/assertion.hpp"


#include "ext/hashing.ixx"
#include "ext/keywords.ixx"



#include "dom/detail/shadow_internals.hpp"
#include "dom/detail/tree_internals.hpp"


#include "dom/nodes/shadow_root.hpp"
#include "dom/nodes/window.hpp"

#include "event_timing/detail/timing_internals.hpp"
#include "event_timing/performance_event_timing.hpp"

#include "hr_time/detail/time_internals.hpp"
#include "indexed_db/events/idb_version_change_event.hpp"
#include "pointer_events/pointer_event.hpp"
#include "touch_events/touch_event.hpp"
#include "ui_events/mouse_event.hpp

#include <fmt/format.h>
#include <range/v3/to_container.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/empty.hpp>
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/slice.hpp>


auto dom::detail::flatten_more(
        event_listener_options_t&& options)
        -> ext::map<ext::string, ext::any>
{
    // Return {capture: true} if the options is a bool value, otherwise the map already being held in the variant
    // object. This just acts as a normalizer to get the "capture" value in map form.
    return ext::holds_alternative<ext::boolean>(options)
           ? ext::map<ext::string, ext::any>{{u"capture", ext::get<ext::boolean>(options)}}
           : ext::get<ext::map<ext::string, ext::any>>(options);
}


auto dom::detail::flatten(
        event_listener_options_t&& options)
        -> ext::boolean
{
    // Return the boolean "capture" value if a boolean value is being stored in the variant, otherwise the capture
    // option of the map. This just acts as a normalizer to get the boolean representation of the "capture" value
    return ext::holds_alternative<ext::boolean>(options)
           ? ext::get<ext::boolean>(options)
           : ext::get<ext::map<ext::string, ext::any>>(options).at(u"capture").to<ext::boolean>();
}


auto dom::detail::remove_all_event_listeners(
        nodes::event_target* const event_target)
        -> void
{
    // Iterate over the event listeners of the 'event_target', and remove each listener from the 'event_target' using
    // the predefined removal algorithm defined in the EventTarget class.
    for (decltype(auto) existing_listener: event_target->m_event_listeners)
        event_target->remove_event_listener(
                existing_listener.at(u"type").to<ext::string>(),
                existing_listener.at(u"callback").to<detail::event_listener_callback_t>(),
                std::move(existing_listener));
}


template <ext::inherit<dom::events::event> T>
auto dom::detail::fire_event(
        ext::string&& e,
        nodes::event_target* target,
        ext::map<ext::string, ext::any>&& init)
        -> ext::boolean
{
    using namespace std::string_literals;

    string_switch(e)
    {
        string_case(u"pointerover"):
        string_case(u"pointerdown"):
        string_case(u"pointermove"):
        string_case(u"pointerup"):
        string_case(u"pointerout"):
            init.template insert_or_assign(u"bubbles", true);
            init.template insert_or_assign(u"cancelable", true);
            break;

        string_case(u"pointerenter"):
        string_case(u"pointerleave"):
        string_case(u"load"):
        string_case(u"unload"):
        string_case(u"abort"):
        string_case(u"error"):
            init.template insert_or_assign(u"bubbles", false);
            init.template insert_or_assign(u"cancelable", false);
            break;

        string_case(u"pointerrawupdate"):
        string_case(u"pointercancel"):
        string_case(u"gotpointercapture"):
        string_case(u"lostpointercapture"):
        string_case(u"select"):
        string_case(u"animationstart"):
        string_case(u"animationend"):
        string_case(u"animationiteration"):
        string_case(u"animationcancelable"):
            init.template insert_or_assign(u"bubbles", true);
            init.template insert_or_assign(u"cancelable", false);
            break;

        string_case(u"touchcancel"):
            init.template insert_or_assign(u"cancelable", false);
            init.template insert_or_assign(u"bubbles", true);
            init.template insert_or_assign(u"composed", true);
            break;

        string_case(u"blur"):
        string_case(u"focus"):
        string_case(u"mouseenter"):
        string_case(u"mouseleave"):
            init.template insert_or_assign(u"bubbles", false);
            init.template insert_or_assign(u"cancelable", false);
            init.template insert_or_assign(u"composed", true);
            break;

        string_case(u"focusin"):
        string_case(u"focusout"):
        string_case(u"input"):
        string_case(u"compositionupdate"):
        string_case(u"compositionend"):
            init.template insert_or_assign(u"bubbles", true);
            init.template insert_or_assign(u"cancelable", false);
            init.template insert_or_assign(u"composed", true);
            break;

        string_case(u"auxclick"):
        string_case(u"click"):
        string_case(u"contextmenu"):
        string_case(u"dblclick"):
        string_case(u"mousedown"):
        string_case(u"mousemove"):
        string_case(u"mouseout"):
        string_case(u"mouseover"):
        string_case(u"mouseup"):
        string_case(u"beforeinput"):
        string_case(u"keydown"):
        string_case(u"keyup"):
        string_case(u"compositionstart"):
            init.template insert_or_assign(u"bubbles", true);
            init.template insert_or_assign(u"cancelable", true);
            init.template insert_or_assign(u"composed", true);
            break;

        string_case(u"wheel"):
        string_case(u"touchstart"):
        string_case(u"touchend"):
        string_case(u"touchmove"):
            init.template insert_or_assign(u"bubbles", true);
            init.template insert_or_assign(u"composed", true);
            break;
    }

    if constexpr (type_is<T, indexed_db::events::idb_version_change_event>)
    {
        init.template insert_or_assign(u"bubbles", false);
        init.template insert_or_assign(u"cancelable", false);
    }

    // create a new event of type T, setting the event type and options, and then dispatch it to 'target'
    T event {std::move(e), std::move(init)};
    return dispatch(&event, target);
}
